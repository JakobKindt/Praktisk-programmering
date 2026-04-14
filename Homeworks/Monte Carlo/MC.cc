#include"MC.h"
#include<random>

// matrix get_sample(pp::vec& a, pp::vec& b, int N){
//     int dim = a.size();
//     for(int i = 0; i < dim; ++i){if (b[i] < a[i]) throw std::runtime_error("b[" + std::to_string(i) + "] = " + std::to_string(b[i]) + " > a[" + std::to_string(i) + "] = " + std::to_string(a[i]) + ".");};
//     matrix X(N, dim);

//     std::uniform_real_distribution<double> unif(0, 1);
//     std::default_random_engine re;
//     double r;
//     for (int i = 0; i < N; ++i){
//         for (int j = 0; j < dim; ++j){
//             r = unif(re);
//             X[j, i] = a[j] + r*(b[j] - a[j]);
//             }
//         }
//     return X;
// };


pp::vec MC(std::function<double(pp::vec)> f, pp::vec& a, pp::vec& b, int N){
    int dim = a.size();
    double V = 1;
    for(int i = 0; i < dim; ++i){V *= b[i]-a[i]; if (b[i] < a[i]) throw std::runtime_error("b[" + std::to_string(i) + "] = " + std::to_string(b[i]) + " > a[" + std::to_string(i) + "] = " + std::to_string(a[i]) + ".");};
    pp::vec x(dim);

    std::uniform_real_distribution<double> unif(0, 1);
    std::default_random_engine re;
    double r, sum = 0, sum2 = 0;
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < dim; ++j){
            r = unif(re);
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

// double corput(int n, int b){
//     double f = 1,
//            r = 0;
//     while(n > 0) {
//         f /= b;
//         r += (n % b) * f;
//         n = std::floor(n/b);
//     }
//     return r;
// }



pp::vec QMC(std::function<double(pp::vec)> f, pp::vec& a, pp::vec& b, int N, int M, std::vector<int> base_primes){
    
    int dim = a.size();
    std::vector<int> primes(dim);
    double V = 1;
    pp::vec x(dim), means(M);
    double r, prime, sum;
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
            sum += f(x);;
            }
        means[k] = V*sum/N;
        // std::cout << "primes = {";
        // for (int i = 0; i < int(primes.size() - 1); ++i){std::cout << primes[i] << ", ";}
        // std::cout << primes[primes.size() - 1] << "}.\n";
    }
    means.print("means = ");
    double mean = 0, sigma = 0;
    for (int k = 0; k < M; ++k){mean += means[k];}
    mean /= M;
    for (int k = 0; k < M; ++k){sigma += (means[k] - mean)*(means[k] - mean);}
    sigma = std::sqrt(sigma/(M - 1));
    
    pp::vec res{mean, sigma};
    return res;
};

//  for(int i = 0; i < dim; ++i){
//         if (b[i] < a[i]) throw std::runtime_error("b[" + std::to_string(i) + "] = " + std::to_string(b[i]) + " > a[" + std::to_string(i) + "] = " + std::to_string(a[i]) + ".");
//         V *= b[i]-a[i]; 
//         primes[i] = base_primes[i];
//     }
    
//     for (int i = 0; i < N; ++i){
//         for (int j = 0; j < dim; ++j){
//             r = corput(i, primes[j]);
//             x[j] = a[j] + r*(b[j] - a[j]);
//             }
//         double fx = f(x); sum += fx; sum2 += fx*fx;
//         }
//     double mean = sum/N, sigma = std::sqrt(sum2/N - mean*mean);
//     pp::vec res{mean*V, sigma*V/std::sqrt(N)};
//     return res;







// pp::vec QMC(std::function<double(pp::vec)> f, pp::vec& a, pp::vec& b, int N, std::vector<int> base_primes){
    
//     int dim = a.size();
//     std::vector<int> primes(dim);
//     double V = 1;
//     for(int i = 0; i < dim; ++i){
//         if (b[i] < a[i]) throw std::runtime_error("b[" + std::to_string(i) + "] = " + std::to_string(b[i]) + " > a[" + std::to_string(i) + "] = " + std::to_string(a[i]) + ".");
//         V *= b[i]-a[i]; 
//         primes[i] = base_primes[i];
//     }
//     pp::vec x(dim);
//     double r, sum = 0, sum2 = 0;
//     for (int i = 0; i < N; ++i){
//         for (int j = 0; j < dim; ++j){
//             r = corput(i, primes[j]);
//             x[j] = a[j] + r*(b[j] - a[j]);
//             }
//         double fx = f(x); sum += fx; sum2 += fx*fx;
//         }
//     double mean = sum/N, sigma = std::sqrt(sum2/N - mean*mean);
//     pp::vec res{mean*V, sigma*V/std::sqrt(N)};
//     return res;
// };