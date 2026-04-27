#pragma once
#include<functional>
#include"matrix.h"
#include"min.h"

// class ann{
//     int n; /* number of hidden neurons */
//     std::function<double(double)> f = [](double x){return x*std::exp(-x*x);}; /* activation function */
//     matrix p; /* network parameters */
//     std::function<double(pp::vec)> loss = [&p, y](pp::vec x){
//             int dim = x.size();
//             double sum = 0;
//             double value;
//             for (int i = 0; i < dim; ++i){value = (response(x[i]) - y[i]); sum += value*value;}
//             return sum;
//         };
//     ann(int n){n = n; /* constructor */}
//     double response(double x){/* return the response of the network to the input signal x */
//         double sum = 0;
//         for (int i = 0; i < n; ++i){sum += f((x - p[i, 0])/p[i, 1])*p[i, 2];}
//         return sum;
//     }
//     void train(pp::vec x, pp::vec y){
//         p = matrix(3, x.size()); p += 1;
//         pp::vec start(x.size()); start += 1;
//         std::tuple<double, pp::vec, int> res = newton_central(loss, start);
//         /* train the network to interpolate the given table {x,y} */
//     }
// };

// class ann{
// public: 
//     int n; /* number of hidden neurons */
//     std::function<double(double)> f = [](double x){return x*std::exp(-x*x);}; /* activation function */
//     pp::vec p; /* network parameters */
//     ann(int n){n = n; /* constructor */}
//     double response(double x, pp::vec& q){/* return the response of the network to the input signal x */
//         double sum = 0;
//         for (int i = 0; i < n; ++i){sum += f((x - q[0])/q[1])*q[2];}
//         return sum;
//     }
//     void train(pp::vec x, pp::vec y){
//         p = pp::vec(3); p += 1.1;
//         std::function<double(pp::vec)> loss = [&](pp::vec p){
//             int dim = x.size();
//             double sum = 0, value;
//             for (int i = 0; i < dim; ++i){value = response(x[i], p) - y[i]; sum += value*value;}
//             return sum;
//         };
//         // pp::vec start(x.size()); start += 1;
//         std::tuple<double, pp::vec, int> res = newton_central(loss, p);
//         /* train the network to interpolate the given table {x,y} */
//     }
// };



// class ann{
// public: 
//     int n; /* number of hidden neurons */
//     std::function<double(double)> f = [](double x){return x*std::exp(-x*x);}; /* activation function */
//     pp::vec p; /* network parameters */
//     matrix P;
//     ann(int n){this ->n = n; /* constructor */}
//     double response(double x, pp::vec& q);/* return the response of the network to the input signal x */
//     double response(double x);
//     void train(pp::vec& x, pp::vec& y); /* train the network to interpolate the given table {x,y} */
// };

class ann{
public: 
    int n; /* number of hidden neurons */
    // std::function<double(double)> f = [](double x){return std::cos(5*x)*std::exp(-x*x);}; /* activation function */
    std::function<double(double)> f = [](double x){return x*std::exp(-x*x);}; /* activation function */
    pp::vec p; /* network parameters */
    matrix P;
    ann(int n){this ->n = n; /* constructor */}
    double response(double x, pp::vec& q);/* return the response of the network to the input signal x */
    double response(double x);
    void train(pp::vec& x, pp::vec& y); /* train the network to interpolate the given table {x,y} */
};