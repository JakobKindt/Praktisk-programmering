#pragma once
#include<functional>
#include"matrix.h"

pp::vec gradient(std::function<double(pp::vec)>& phi, pp::vec& x);

class ann{
public: 
    int n; /* number of hidden neurons */
    double lr, tol; /* learning rate*/
    // std::function<double(double)> f = [](double x){return std::cos(5*x)*std::exp(-x*x);}; /* activation function */
    std::function<double(double)> f = [](double x){return x*std::exp(-x*x);}; /* activation function */
    std::function<double(double)> F = [](double x){return -std::exp(-x*x)/2;}; /* antiderivative of activation function */
    std::function<double(double)> df = [](double x){return (1-2*x*x)*std::exp(-x*x);}; /* derivative of activation function */
    std::function<double(double)> ddf = [](double x){return (4*x*x*x - 6*x)*std::exp(-x*x);}; /* double derivative of activation function */
    pp::vec p; /* network parameters */
    matrix P;
    ann(int n, double lr, double tol){this ->n = n; this -> lr = lr; this -> tol = tol; /* constructor */}
    double response(double x, pp::vec& q);/* return the response of the network to the input signal x */
    double response(double x);
    pp::vec total_response(double x); /* Includes antiderivative, derivative, double derivative and response */
    void train(pp::vec& x, pp::vec& y); /* train the network to interpolate the given table {x,y} */
};