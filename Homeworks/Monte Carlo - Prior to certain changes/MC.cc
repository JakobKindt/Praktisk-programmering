#include"MC.h"
#include<random>
#include<cmath>

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
// Player::Player(Vector2 position, Vector2 velocity, float width, float height, Color color)
//     : pos(position), v(velocity), width(width), height(height), color(color){}
// class Player
// {
// public:
//     Player(Vector2 position, Vector2 velocity, float width, float height, Color color);

//     void Update(const std::vector<Wall>& walls, const Wall& goal);
//     void Draw() const;
//     Rectangle GetRect() const;
//     void DrawHitbox(bool isColliding);
//     Vector2 pos;       // Position
//     bool goal_reached = false;
// private:
//     void HandleInput(bool standing);

//     Vector2 v;     // Velocity
//     float width;       // width
//     float height;
// }

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

    // if (generator_type == 0){auto re = re_lcg;}
    // else {auto re = re_built_in;}
    double r, sum = 0, sum2 = 0;
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < dim; ++j){
            // r = re.next();
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
            sum += f(x);;
            }
        means[k] = V*sum/N;
        // std::cout << "primes = {";
        // for (int i = 0; i < int(primes.size() - 1); ++i){std::cout << primes[i] << ", ";}
        // std::cout << primes[primes.size() - 1] << "}.\n";
    }
    // means.print("means = ");
    double mean = 0, sigma = 0;
    for (int k = 0; k < M; ++k){mean += means[k];}
    mean /= M;
    for (int k = 0; k < M; ++k){sigma += (means[k] - mean)*(means[k] - mean);}
    sigma = std::sqrt(sigma/(M - 1));
    
    pp::vec res{mean, sigma};
    return res;
};
// USING NMIN AND N

pp::vec SMC(std::function<double(pp::vec)> f, pp::vec& a, pp::vec& b, int N, int nmin, int generator_type){
    if (N < nmin){return MC(f, a, b, N);}
    int dim = a.size();
    pp::vec x(dim), mean_left(dim), mean_right(dim), n_left(dim), n_right(dim);

    // std::uniform_real_distribution<double> unif(0, 1);
    // std::default_random_engine re;
    
    // else {auto re = re_built_in;}
    double r, fx, var, varmax = 0;
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
            if (x[j] > (b[j] + a[j])/2){mean_right[j] += fx; ++n_right[j];} //Note n_right is not actually integers because I use my own non-templated vector class.
            else{mean_left[j] += fx; ++n_left[j];}
        }
    }

    mean_left /= n_left; mean_right /= n_right;
    for (int j = 0; j < dim; ++j){
        var = std::abs(mean_left[j] - mean_right[j]);
        if (var > varmax){n = j; varmax = var;}
    }
    pp::vec b_new = b, a_new = a;
    b_new[n] = (b[n] + a[n])/2; a_new[n] = (b[n] + a[n])/2;
    int N_left = n_left[n], N_right = n_right[n];

    pp::vec res_left = SMC(f, a, b_new, N_left, nmin), res_right = SMC(f, a_new, b, N_right, nmin);
    double integral = res_left[0] + res_right[0];
    double err = std::sqrt(res_left[1]*res_left[1] + res_right[1]*res_right[1]);
    pp::vec res{integral, err};
    return res;
};


// std::uniform_real_distribution<double> unif(0, 1);
// std::default_random_engine re;
// pp::vec MC(std::function<double(pp::vec)> f, pp::vec& a, pp::vec& b, int N){
//     int dim = a.size();
//     double V = 1;
//     for(int i = 0; i < dim; ++i){V *= b[i]-a[i]; if (b[i] < a[i]) throw std::runtime_error("b[" + std::to_string(i) + "] = " + std::to_string(b[i]) + " > a[" + std::to_string(i) + "] = " + std::to_string(a[i]) + ".");};
//     pp::vec x(dim);

    
//     double r, sum = 0, sum2 = 0;
//     for (int i = 0; i < N; ++i){
//         for (int j = 0; j < dim; ++j){
//             r = unif(re);
//             x[j] = a[j] + r*(b[j] - a[j]);
//             }
//         double fx = f(x); sum += fx; sum2 += fx*fx;
//         }
//     double mean = sum/N, sigma = std::sqrt(sum2/N - mean*mean);
//     pp::vec res{mean*V, sigma*V/std::sqrt(N)};
//     return res;
// };


// double corput(int n, int b){
//     double q = 0, bk = 1./b;
//     while (n > 0){q += n % b*bk; n /= b; bk /= b;};
//     return q;
// }


// pp::vec QMC(std::function<double(pp::vec)> f, pp::vec& a, pp::vec& b, int N, int M, std::vector<int> base_primes){
//     int dim = a.size();
//     std::vector<int> primes(dim);
//     double r, sum, V = 1;
//     pp::vec x(dim), means(M);
//     int prime;
//     for(int i = 0; i < dim; ++i){
//         if (b[i] < a[i]) throw std::runtime_error("b[" + std::to_string(i) + "] = " + std::to_string(b[i]) + " > a[" + std::to_string(i) + "] = " + std::to_string(a[i]) + ".");
//         V *= b[i] - a[i]; 
//     }

//     std::random_device dev;
//     std::mt19937 rng(dev());
//     std::uniform_int_distribution<std::mt19937::result_type> dist(0, base_primes.size() - 1);

//     bool allowed_prime = true;
//     int max_attempts =  5000;
//     for (int k = 0; k < M; ++k){
//         primes = std::vector<int>(dim);
//         sum = 0;
//         for (int i = 0; i < dim; ++i){
//             for (int stopping = 0; stopping < max_attempts; ++stopping){
//                 allowed_prime = true;
//                 prime = base_primes[dist(rng)];
//                 for (int j = 0; j < i; ++j){if (primes[j] == prime){allowed_prime = false; break;}}
//                 if (allowed_prime){primes[i] = prime; break;}
//                 if (stopping == max_attempts - 1){throw std::runtime_error("Could not find enough independent primes for basis");}
//             }
//         }
    
//         for (int i = 0; i < N; ++i){
//             for (int j = 0; j < dim; ++j){
//                 r = corput(i, primes[j]);
//                 x[j] = a[j] + r*(b[j] - a[j]);
//                 }
//             sum += f(x);;
//             }
//         means[k] = V*sum/N;
//         // std::cout << "primes = {";
//         // for (int i = 0; i < int(primes.size() - 1); ++i){std::cout << primes[i] << ", ";}
//         // std::cout << primes[primes.size() - 1] << "}.\n";
//     }
//     // means.print("means = ");
//     double mean = 0, sigma = 0;
//     for (int k = 0; k < M; ++k){mean += means[k];}
//     mean /= M;
//     for (int k = 0; k < M; ++k){sigma += (means[k] - mean)*(means[k] - mean);}
//     sigma = std::sqrt(sigma/(M - 1));
    
//     pp::vec res{mean, sigma};
//     return res;
// };
// // USING NMIN AND N

// pp::vec SMC(std::function<double(pp::vec)> f, pp::vec& a, pp::vec& b, int N, int nmin){
//     if (N < nmin){return MC(f, a, b, N);}
//     int dim = a.size();
//     pp::vec x(dim), mean_left(dim), mean_right(dim), n_left(dim), n_right(dim);

//     std::uniform_real_distribution<double> unif(0, 1);
//     std::default_random_engine re;
//     double r, fx, var, varmax = 0;
//     int n = 0;
//     for (int i = 0; i < N; ++i){
//         for (int j = 0; j < dim; ++j){
//             r = unif(re);
//             x[j] = a[j] + r*(b[j] - a[j]);
//             }
//         fx = f(x);
//         for (int j = 0; j < dim; ++j){
//             if (x[j] > (b[j] + a[j])/2){mean_right[j] += fx; ++n_right[j];} //Note n_right is not actually integers because I use my own non-templated vector class.
//             else{mean_left[j] += fx; ++n_left[j];}
//         }
//     }

//     mean_left /= n_left; mean_right /= n_right;
//     for (int j = 0; j < dim; ++j){
//         var = std::abs(mean_left[j] - mean_right[j]);
//         if (var > varmax){n = j; varmax = var;}
//     }
//     pp::vec b_new = b, a_new = a;
//     b_new[n] = (b[n] + a[n])/2; a_new[n] = (b[n] + a[n])/2;
//     int N_left = n_left[n], N_right = n_right[n];

//     pp::vec res_left = SMC(f, a, b_new, N_left, nmin), res_right = SMC(f, a_new, b, N_right, nmin);
//     double integral = res_left[0] + res_right[0];
//     double err = std::sqrt(res_left[1]*res_left[1] + res_right[1]*res_right[1]);
//     pp::vec res{integral, err};
//     return res;
// };









































// Other error estimation:
// pp::vec SMC(std::function<double(pp::vec)> f, pp::vec& a, pp::vec& b, double acc, double eps, int n_reuse, double mean_reuse, double err_reuse){
//     int dim = a.size(), N = 32*dim;
//     double V = 1;
//     for(int i = 0; i < dim; ++i){
//         if (b[i] < a[i]) throw std::runtime_error("b[" + std::to_string(i) + "] = " + std::to_string(b[i]) + " > a[" + std::to_string(i) + "] = " + std::to_string(a[i]) + ".");
//         V *= b[i] - a[i]; 
//     }
//     pp::vec x(dim), mean_left(dim), mean_right(dim), n_left(dim), n_right(dim), sum2_right(dim), sum2_left(dim);

//     double r, fx, var, varmax = 0, mean = 0, sum2 = 0;
//     int n = 0;
//     for (int i = 0; i < N; ++i){
//         for (int j = 0; j < dim; ++j){
//             r = unif(re);
//             x[j] = a[j] + r*(b[j] - a[j]);
//             }
//         fx = f(x);
//         mean += fx;
//         sum2 += fx*fx;
//         for (int j = 0; j < dim; ++j){
//             if (x[j] > (b[j] + a[j])/2){mean_right[j] += fx; ++n_right[j]; sum2_right[j] += fx*fx;} //Note n_right is not actually integers because I use my own non-templated vector class.
//             else{mean_left[j] += fx; ++n_left[j]; sum2_left[j] += fx*fx;}
//         }
//     }

//     mean /= N;
//     mean_left /= n_left; mean_right /= n_right;
//     for (int j = 0; j < dim; ++j){
//         var = std::abs(mean_left[j] - mean_right[j]);
//         if (var > varmax){n = j; varmax = var;}
//     }
//     // double mean = sum/N, 
//     double sigma = std::sqrt(sum2/N - mean*mean)*V/std::sqrt(N), sigma_left = std::sqrt(sum2_left[n]/n_left[n] - mean_left[n]*mean_left[n])*V/std::sqrt(n_left[n])/2, sigma_right = std::sqrt(sum2_right[n]/n_right[n] - mean_right[n]*mean_right[n])*V/std::sqrt(n_right[n])/2;
//     double err = std::sqrt(sigma*sigma + err_reuse*err_reuse), err_left = std::sqrt(sigma_left*1e16*sigma_left + err_reuse*1e16*err_reuse)*1e-8, err_right = std::sqrt(sigma_right*1e16*sigma_right + err_reuse*1e16*err_reuse)*1e-8;
    
//     std::cout << "sigmas " << sigma_left << "\t" << sigma_right << "\t" << err_reuse << "\t" << acc << "\n";

//     // pp::vec res{mean*V, sigma*V/std::sqrt(N)};


//     double integral = (mean*N + mean_reuse*n_reuse)/(N + n_reuse) * V;
//     // double err = std::abs(mean_reuse - mean)*V;
//     double tol = acc + std::abs(integral)*eps;
//     if (err < tol){return pp::vec{integral, err};}



//     pp::vec b_new = b, a_new = a;
//     b_new[n] = (b[n] + a[n])/2; a_new[n] = (b[n] + a[n])/2;

//     pp::vec res_left = SMC(f, a, b_new, acc/std::sqrt(2), eps, n_left[n], mean_left[n], err_left), res_right = SMC(f, a_new, b, acc/std::sqrt(2), eps, n_right[n], mean_right[n], err_right);
//     // pp::vec res_left = SMC(f, a, b_new, acc/std::sqrt(2), eps, n_left[n], mean_left[n], sigma_left), res_right = SMC(f, a_new, b, acc/std::sqrt(2), eps, n_right[n], mean_right[n], sigma_right);
    
//     // integral = res_left[0] + res_right[0];
//     err = std::sqrt(res_left[1]*res_left[1] + res_right[1]*res_right[1]);
//     pp::vec res{integral, err};
//     return res;
// };


// pp::vec SMC(std::function<double(pp::vec)> f, pp::vec& a, pp::vec& b, double acc, double eps, int n_reuse, double mean_reuse, double err_reuse){
//     int dim = a.size(), N = 32*dim;
//     double V = 1;
//     for(int i = 0; i < dim; ++i){
//         if (b[i] < a[i]) throw std::runtime_error("b[" + std::to_string(i) + "] = " + std::to_string(b[i]) + " > a[" + std::to_string(i) + "] = " + std::to_string(a[i]) + ".");
//         V *= b[i] - a[i]; 
//     }
//     pp::vec x(dim), mean_left(dim), mean_right(dim), n_left(dim), n_right(dim), sum2_right(dim), sum2_left(dim);

//     double r, fx, var, varmax = 0, mean = 0, sum2 = 0;
//     int n = 0;
//     for (int i = 0; i < N; ++i){
//         for (int j = 0; j < dim; ++j){
//             r = unif(re);
//             x[j] = a[j] + r*(b[j] - a[j]);
//             }
//         fx = f(x);
//         mean += fx;
//         sum2 += fx*fx;
//         for (int j = 0; j < dim; ++j){
//             if (x[j] > (b[j] + a[j])/2){mean_right[j] += fx; ++n_right[j]; sum2_right[j] += fx*fx;} //Note n_right is not actually integers because I use my own non-templated vector class.
//             else{mean_left[j] += fx; ++n_left[j]; sum2_left[j] += fx*fx;}
//         }
//     }

//     mean /= N;
//     mean_left /= n_left; mean_right /= n_right;
//     for (int j = 0; j < dim; ++j){
//         var = std::abs(mean_left[j] - mean_right[j]);
//         if (var > varmax){n = j; varmax = var;}
//     }
//     // double mean = sum/N, 
//     double sigma = std::sqrt(sum2/N - mean*mean)*V/std::sqrt(N), sigma_left = std::sqrt(sum2_left[n]/n_left[n] - mean_left[n]*mean_left[n])*V/std::sqrt(n_left[n])/2, sigma_right = std::sqrt(sum2_right[n]/n_right[n] - mean_right[n]*mean_right[n])*V/std::sqrt(n_right[n])/2;
//     double err = std::sqrt(sigma*sigma + err_reuse*err_reuse);
    

//     // pp::vec res{mean*V, sigma*V/std::sqrt(N)};


//     double integral = (mean*N + mean_reuse*n_reuse)/(N + n_reuse) * V;
//     // double err = std::abs(mean_reuse - mean)*V;
//     double tol = acc + std::abs(integral)*eps;
//     if (err < tol){return pp::vec{integral, err};}



//     pp::vec b_new = b, a_new = a;
//     b_new[n] = (b[n] + a[n])/2; a_new[n] = (b[n] + a[n])/2;

//     pp::vec res_left = SMC(f, a, b_new, acc/std::sqrt(2), eps, n_left[n], mean_left[n], sigma_left), res_right = SMC(f, a_new, b, acc/std::sqrt(2), eps, n_right[n], mean_right[n], sigma_right);
//     integral = res_left[0] + res_right[0];
//     err = std::sqrt(res_left[1]*res_left[1] + res_right[1]*res_right[1]);
//     pp::vec res{integral, err};
//     return res;
// };



//Using acc and eps
// std::uniform_real_distribution<double> unif(0, 1);
// std::default_random_engine re;
// pp::vec SMC(std::function<double(pp::vec)> f, pp::vec& a, pp::vec& b, double acc, double eps, int n_reuse, double mean_reuse){
//     int dim = a.size(), N = 32*dim;
//     double V = 1;
//     for(int i = 0; i < dim; ++i){
//         if (b[i] < a[i]) throw std::runtime_error("b[" + std::to_string(i) + "] = " + std::to_string(b[i]) + " > a[" + std::to_string(i) + "] = " + std::to_string(a[i]) + ".");
//         V *= b[i] - a[i]; 
//     }
//     pp::vec x(dim), mean_left(dim), mean_right(dim), n_left(dim), n_right(dim);

//     double r, fx, var, varmax = 0, mean = 0;
//     int n = 0;
//     for (int i = 0; i < N; ++i){
//         for (int j = 0; j < dim; ++j){
//             r = unif(re);
//             x[j] = a[j] + r*(b[j] - a[j]);
//             }
//         fx = f(x);
//         mean += fx;
//         for (int j = 0; j < dim; ++j){
//             if (x[j] > (b[j] + a[j])/2){mean_right[j] += fx; ++n_right[j];} //Note n_right is not actually integers because I use my own non-templated vector class.
//             else{mean_left[j] += fx; ++n_left[j];}
//         }
//     }
//     mean /= N;
//     mean_left /= n_left; mean_right /= n_right;
//     for (int j = 0; j < dim; ++j){
//         var = std::abs(mean_left[j] - mean_right[j]);
//         if (var > varmax){n = j; varmax = var;}
//     }

//     double integral = (mean*N + mean_reuse*n_reuse)/(N + n_reuse) * V;
//     double err = std::abs(mean_reuse - mean)*V;
//     double tol = acc + std::abs(integral)*eps;
//     if (err < tol){return pp::vec{integral, err};}



//     pp::vec b_new = b, a_new = a;
//     b_new[n] = (b[n] + a[n])/2; a_new[n] = (b[n] + a[n])/2;

//     pp::vec res_left = SMC(f, a, b_new, acc/std::sqrt(2), eps, n_left[n], mean_left[n]), res_right = SMC(f, a_new, b, acc/std::sqrt(2), eps, n_right[n], mean_right[n]);
//     integral = res_left[0] + res_right[0];
//     err = std::sqrt(res_left[1]*res_left[1] + res_right[1]*res_right[1]);
//     pp::vec res{integral, err};
//     return res;
// };


// If N<nmin return N-point plain Monte Carlo estimate of integral and variance;
// Sample nmin points and estimate the integral and the variance;
// Find the dimension with largest sub-variance;
// Subdivide the volume along this dimension;
// Divide the remaning points between the two sub-volumes proportional to sub-variances;
// Dispatch two recursive calls on the sub-volumes;
// Estimate the grand integral and grand error;
// Return the grand integral and the grand error;