#include"matrix.h"
#include<functional>

matrix jacobian(std::function<pp::vec(pp::vec)>& f, pp::vec& x);
matrix jacobian(std::function<pp::vec(pp::vec)>& f, pp::vec& x, pp::vec& fx, pp::vec& dx);
pp::vec newton(std::function<pp::vec(pp::vec)>& f, pp::vec& start, double acc = 1e-2);
// pp::vec minus_ten_vec{-10};
// pp::vec newton(std::function<pp::vec(pp::vec)>& f, pp::vec& start, double acc = 1e-2, pp::vec& delta_x = minus_ten_vec);