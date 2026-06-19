#include"MC.h"
#include<random>
#include<cmath>

lcg::lcg(uint64_t seed, uint64_t a, uint64_t c, uint64_t m): seed(seed), a(a), c(c), m(m){}
double lcg::next(){seed = (a * seed + c) % m; return (seed + 1)/(double)(m + 1);}

std::uniform_real_distribution<double> unif(0, 1);
std::default_random_engine re_built_in;
lcg re_lcg;
pp::vec MC(std::function<double(pp::vec)> f, pp::vec& a, pp::vec& b, int N, int generator_type){
    int dim = a.size();
    double V = 1;
    for(int i = 0; i < dim; ++i){V *= b[i]-a[i]; if (b[i] < a[i]) throw std::runtime_error("b[" + std::to_string(i) + "] = " + std::to_string(b[i]) + " > a[" + std::to_string(i) + "] = " + std::to_string(a[i]) + ".");};
    pp::vec x(dim);

    double r, sum = 0, sum2 = 0;
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < dim; ++j){
            if (generator_type == 0){r = re_lcg.next();}
            else{r = unif(re_built_in);}
            x[j] = a[j] + r*(b[j] - a[j]);
            }
        double fx = f(x); sum += fx; sum2 += fx*fx;
        }
    double mean = sum/N, sigma = std::sqrt(sum2/N - mean*mean);
    pp::vec res{mean*V, sigma*V/std::sqrt(N)};
    return res;
};


double corput(int n, int b){
    double q = 0, bk = 1./b;
    while (n > 0){q += n % b*bk; n /= b; bk /= b;};
    return q;
}


pp::vec QMC(std::function<double(pp::vec)> f, pp::vec& a, pp::vec& b, int N, int M, std::vector<int> base_primes){
    int dim = a.size();
    std::vector<int> primes(dim);
    double r, sum, V = 1;
    pp::vec x(dim), means(M);
    int prime;
    for(int i = 0; i < dim; ++i){
        if (b[i] < a[i]) throw std::runtime_error("b[" + std::to_string(i) + "] = " + std::to_string(b[i]) + " > a[" + std::to_string(i) + "] = " + std::to_string(a[i]) + ".");
        V *= b[i] - a[i]; 
    }

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, base_primes.size() - 1);

    bool allowed_prime = true;
    int max_attempts =  5000;
    for (int k = 0; k < M; ++k){
        primes = std::vector<int>(dim);
        sum = 0;
        for (int i = 0; i < dim; ++i){
            for (int stopping = 0; stopping < max_attempts; ++stopping){
                allowed_prime = true;
                prime = base_primes[dist(rng)];
                for (int j = 0; j < i; ++j){if (primes[j] == prime){allowed_prime = false; break;}}
                if (allowed_prime){primes[i] = prime; break;}
                if (stopping == max_attempts - 1){throw std::runtime_error("Could not find enough independent primes for basis");}
            }
        }
        for (int i = 0; i < N; ++i){
            for (int j = 0; j < dim; ++j){
                r = corput(i, primes[j]);
                x[j] = a[j] + r*(b[j] - a[j]);
                }
            sum += f(x);
            }
        means[k] = V*sum/N;
        // std::cout << "primes = {";
        // for (int i = 0; i < int(primes.size() - 1); ++i){std::cout << primes[i] << ", ";}
        // std::cout << primes[primes.size() - 1] << "}.\n";
    }
    double mean = 0, sigma = 0;
    for (int k = 0; k < M; ++k){mean += means[k];}
    mean /= M;
    for (int k = 0; k < M; ++k){sigma += (means[k] - mean)*(means[k] - mean);}
    sigma = std::sqrt(sigma/(M - 1));
    
    pp::vec res{mean, sigma};
    return res;
};


pp::vec SMC(std::function<double(pp::vec)> f, pp::vec& a, pp::vec& b, int N, int nmin, int generator_type){
    if (N < nmin){return MC(f, a, b, N);}
    int dim = a.size();
    pp::vec x(dim), mean_left(dim), mean_right(dim), var_left(dim), var_right(dim), n_left(dim), n_right(dim);

    double r, fx, var, varmax = -1;
    int n = 0;
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < dim; ++j){
            // r = unif(re);
            if (generator_type == 0){r = re_lcg.next();}
            else{r = unif(re_built_in);}
            x[j] = a[j] + r*(b[j] - a[j]);
            }
        fx = f(x);
        for (int j = 0; j < dim; ++j){
            if (x[j] > (b[j] + a[j])/2){mean_right[j] += fx; ++n_right[j]; var_right[j] += fx*fx;} //Note n_right is not actually integers because I use my own non-templated vector class.
            else{mean_left[j] += fx; ++n_left[j]; var_left[j] += fx*fx;}
        }
    }

    mean_left /= n_left; mean_right /= n_right;
    var_right = var_right/n_right - mean_right*mean_right; var_left = var_left/n_left - mean_left*mean_left;
    for (int j = 0; j < dim; ++j){
        var_right[j] = std::max(var_right[j], 0.); var_left[j] = std::max(var_left[j], 0.); // Prevents rounding error shenanigans.
        var = var_right[j] + var_left[j];
        if (var > varmax){n = j; varmax = var;} // Note that this is not actually a variance
    }
    double var_r = std::sqrt(var_right[n]), var_l = std::sqrt(var_left[n]);
    pp::vec b_new = b, a_new = a;
    b_new[n] = (b[n] + a[n])/2; a_new[n] = (b[n] + a[n])/2;
    int N_left, N_right;
    // int Nprobe = 100; // ChatGPT suggested this. However, even for Nprobe = 1, this increases the |measured - theory|/(estimated err) by a factor of 10, so I have omitted it.
    // N -= Nprobe; // ChatGPT suggested this.
    if (var_l == 0 && var_r == 0){N_left = N/2; N_right = N/2;}
    else{N_left = N*var_l/(var_l + var_r); N_right = N - N_left;}
    N_left = std::max((int)1, N_left); N_right = std::max((int)1, N_right); 
    pp::vec res_left = SMC(f, a, b_new, N_left, nmin, generator_type), res_right = SMC(f, a_new, b, N_right, nmin, generator_type);
    double integral = res_left[0] + res_right[0];
    double err = std::sqrt(res_left[1]*res_left[1] + res_right[1]*res_right[1]);
    pp::vec res{integral, err};
    return res;
};