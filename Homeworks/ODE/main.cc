#include<iostream>
#include<cstdio>
#include"ODE.h"
#include<fstream>
#include<cmath>
#include<functional>

int main(){
    // double a = 0, b = 10;
    // pp::vec y_init{1};
    // std::function<pp::vec(double, pp::vec)> F = [=](double x, pp::vec y){return y*0 + 4*x*x*x;};
    // std::tuple<std::vector<double>, std::vector<pp::vec>> result = driver(F, a, b, y_init);
    
    // std::vector<double> xs = std::get<0>(result);
    // std::vector<pp::vec> ys = std::get<1>(result);
    // for (int i = 0; i < (int)xs.size(); ++i){
    //     std::cout << xs[i] << ", " << ys[i][0] << "\n";
    // }

    // double a = 0, b = 10;
    // pp::vec y_init{0, 1};
    // std::function<pp::vec(double, pp::vec)> F = [=](double x, pp::vec y){
    //     pp::vec dydx(2);
    //     dydx[0] = y[1];
    //     dydx[1] = -y[0] + 0*x;
    //     // y[2] = - y[0] + 0*x;
    //     return dydx;
    // };

    // std::tuple<std::vector<double>, std::vector<pp::vec>> result = driver(F, a, b, y_init);
    
    // std::vector<double> xs = std::get<0>(result);
    // std::vector<pp::vec> ys = std::get<1>(result);
    // for (int i = 0; i < (int)xs.size(); ++i){
    //     std::cout << xs[i] << ", " << ys[i][0] << "\n";
    // } // Sanity check
    
    double a = 0, b = 10;
    pp::vec y_init{0, 1};

    std::function<pp::vec(double, pp::vec)> pend = [=](double x, pp::vec y, double b = 0.3, double c = 7){
        pp::vec dydx(2);
        dydx[0] = y[1] + 0*x;
        dydx[1] = -b*y[1] - c*std::sin(y[0]);
        return dydx;
    };

    std::tuple<std::vector<double>, std::vector<pp::vec>> result = driver(pend, a, b, y_init);
    std::vector<double> xs = std::get<0>(result);
    std::vector<pp::vec> ys = std::get<1>(result);

    std::string outfile = "pend.txt";
    std::ofstream output_pend(outfile);
    for (int i = 0; i < (int)xs.size(); ++i){
        output_pend << xs[i] << ", " << ys[i][0] << "\n";
    }
    output_pend.close();

    y_init = pp::vec {10, 5};
    std::function<pp::vec(double, pp::vec)> lotkavolterra = [=](double x, pp::vec y, double a = 1.5, double b = 1, double c = 3, double d = 1){
        pp::vec dydx(2);
        dydx[0] = a*y[0] - b*y[0]*y[1] + 0*x;
        dydx[1] = -c*y[1] + d*y[0]*y[1];
        return dydx;
    };
    result = driver(lotkavolterra, a, b, y_init);
    xs = std::get<0>(result);
    ys = std::get<1>(result);

    outfile = "lot.txt";
    std::ofstream output_lot(outfile);
    for (int i = 0; i < (int)xs.size(); ++i){
        output_lot << xs[i] << ", " << ys[i][0] << ", " << ys[i][1] << "\n";
    }
    output_lot.close();
    // def lotkavolterra(t, z, a, b, c, d):
    // x, y = z
    // return [a*x - b*x*y, -c*y + d*x*y]
    // exponential_decay(t, y): return -0.5 * y
return 0;
}