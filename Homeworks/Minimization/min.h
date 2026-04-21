#include"QR-factorization.h"
#include"matrix.h"
#include<functional>
#include<tuple>

std::tuple<double, pp::vec, int> newton(std::function<double(pp::vec)>& phi, pp::vec x, double acc = 1e-3, int max_count = 1000);
pp::vec gradient(std::function<double(pp::vec)>& phi, pp::vec& x);
matrix hessian(std::function<double(pp::vec)>& phi, pp::vec& x);

// double newton(std::function<double(pp::vec)>& phi, pp::vec x, double acc = 1e-3);
// pp::vec gradient(std::function<double(pp::vec)>& phi, pp::vec& x);
// matrix hessian(std::function<double(pp::vec)>& phi, pp::vec& x);