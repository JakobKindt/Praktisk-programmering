#include"matrix.h"
#include<functional>

matrix jacobian(std::function<pp::vec(pp::vec)>& f, pp::vec& x);
matrix jacobian(std::function<pp::vec(pp::vec)>& f, pp::vec& x, pp::vec& fx, pp::vec& dx);
pp::vec newton(std::function<pp::vec(pp::vec)>& f, pp::vec& start, double acc = 1e-2);
void update_inverse_jacobian(pp::vec& df, pp::vec& dx, matrix& B);
pp::vec quasi_newton(std::function<pp::vec(pp::vec)>& f, pp::vec& start, double acc = 1e-2);