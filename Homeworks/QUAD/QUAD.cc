#include"QUAD.h"
#include<cmath>
inline double pi = 3.1415926535897932384626433;
double integrate(std::function<double(double)> f, double a, double b, double acc, double eps, double f2, double f3) // NaN indicates first call
{
    double h = b - a;
    if(std::isnan(f2)){f2 = f(a+2*h/6); f3 = f(a+4*h/6);} // first call, no points to reuse
    double f1 = f(a+h/6), f4 = f(a+5*h/6);
    double Q = (2*f1+f2+f3+2*f4)/6*(b - a); // higher order rule
    double q = (  f1+f2+f3+  f4)/4*(b - a); // lower order rule
    double err = std::abs(Q - q);
    if (err <= acc + eps*std::abs(Q)){return Q;}
    else {return integrate(f, a, (a + b)/2, acc/std::sqrt(2), eps, f1, f2) + integrate(f, (a + b)/2, b, acc/std::sqrt(2), eps, f3, f4);};
};


double integrate_CC(std::function<double(double)> f, double a, double b, double acc, double eps){
    if (std::isinf(a) && a < 0 && std::isinf(b) && b > 0){ // eq. 62
        std::function<double(double)> F = [=](double t){
            if (t == 0){return 0.;}
            double value = (1 - t)/t;
            return (f(value) + f(-value))/t/t;
        };
        return integrate_CC(F, 0., 1., acc, eps);
    }
    if (std::isinf(a) && a < 0){ // eq. 66
        std::function<double(double)> F = [=](double t){
            if (t == 0){return 0.;}
            double value = (1 - t)/t;
            return f(b - value)/t/t;
        };
        return integrate_CC(F, 0., 1., acc, eps);
    }
    if (std::isinf(b) && b > 0){ // eq. 64
        std::function<double(double)> F = [=](double t){
            if (t == 0){return 0.;}
            double value = (1 - t)/t;
            return f(a + value)/t/t;
        };
        return integrate_CC(F, 0., 1., acc, eps);
    }
    std::function<double(double)> F = [=](double theta){
        double value = (a + b)/2 + (b - a)/2*std::cos(theta);
        return f(value)*std::sin(theta)*(b - a)/2;
    };
    return integrate(F, 0., pi, acc, eps);
};


std::tuple<double, double> integrate_with_err(std::function<double(double)> f, double a, double b, double acc, double eps, double f2, double f3) // NaN indicates first call
{
    double h = b - a;
    if(std::isnan(f2)){f2 = f(a+2*h/6); f3 = f(a+4*h/6);} // first call, no points to reuse
    double f1 = f(a+h/6), f4 = f(a+5*h/6);
    double Q = (2*f1+f2+f3+2*f4)/6*(b - a); // higher order rule
    double q = (  f1+f2+f3+  f4)/4*(b - a); // lower order rule
    double err = std::abs(Q - q);
    if (err <= acc + eps*std::abs(Q)){return std::make_tuple(Q, err);}
    else {
        double Q1, Q2, err1, err2;
        std::tie(Q1, err1) = integrate_with_err(f, a, (a + b)/2, acc/std::sqrt(2), eps, f1, f2);
        std::tie(Q2, err2) = integrate_with_err(f, (a + b)/2, b, acc/std::sqrt(2), eps, f3, f4);
        return std::make_tuple(Q1 + Q2, std::sqrt(err1*err1 + err2*err2));
    };
};