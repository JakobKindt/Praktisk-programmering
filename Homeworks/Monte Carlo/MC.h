#pragma once
#include"matrix.h"
#include<functional>
#include<vector>
#include<cstdint>
// matrix get_sample(pp::vec& a, pp::vec& b, int N = 5000);
// Here is the first 168 primes (between 1-1000) from https://www.primenumberslist.com/prime-numbers-1-1000.html
// inline std::vector<int> base_primes{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997};
// inline std::vector<int> base_primes{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};
inline std::vector<int> base_primes{2, 3, 5};

pp::vec MC(std::function<double(pp::vec)> f, pp::vec& a, pp::vec& b, int N = 1e6, int generator_type = 0);
double corput(int n, int b = 2);
pp::vec QMC(std::function<double(pp::vec)> f, pp::vec& a, pp::vec& b, int N = 1e6, int M = 1e4, std::vector<int> base_primes = base_primes);
pp::vec SMC(std::function<double(pp::vec)> f, pp::vec& a, pp::vec& b, int N = 1e6, int nmin = 1e3, int generator_type = 0); // USING NMIN AND N
// pp::vec SMC(std::function<double(pp::vec)> f, pp::vec& a, pp::vec& b, double acc = 1e-6, double eps = 1e-6, int n_reuse = 0, double mean_reuse = 0, double err_reuse = 0);
// pp::vec QMC(std::function<double(pp::vec)> f, pp::vec& a, pp::vec& b, int N = 1e6, std::vector<int> base_primes = base_primes);
class lcg{
public:
    lcg(uint64_t seed = 15648964, uint64_t a = 1664525, uint64_t c = 1013904223, uint64_t m = 4294967296);
    double next();
    // int next_digit();
private:
    uint64_t seed, a, c, m;
};