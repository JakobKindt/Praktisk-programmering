#pragma once
#include<functional>
#include<limits>
inline double NaN = std::numeric_limits<double>::quiet_NaN();
double integrate(std::function<double(double)> f, double a, double b, double acc = 0.001, double eps = 0.001, double f2 = NaN, double f3 = NaN); // NaN indicates first call
double integrate_CC(std::function<double(double)> f, double a, double b, double acc = 0.001, double eps = 0.001);