#include"matrix.h"
#include<functional>
std::tuple<pp::vec, pp::vec> rkstep12(std::function<pp::vec(double, pp::vec)> f, double x, pp::vec y, double h);
std::tuple<std::vector<double>, std::vector<pp::vec>> driver(std::function<pp::vec(double, pp::vec)> F, double a, double b, pp::vec yinit, double h=0.125, double acc=0.01, double eps=0.01);