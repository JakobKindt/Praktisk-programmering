#include"ANN.h"
#include<random>

double ann::response(double x, pp::vec& q){/* return the response of the network to the input signal x */
    double sum = 0;
    for (int i = 0; i < n; ++i){sum += f((x - q[i])/q[n + i])*q[2*n + i];}
    return sum;
}

double ann::response(double x){return response(x, p);}

void ann::train(pp::vec& x, pp::vec& y){ /* train the network to interpolate the given table {x,y} */
    std::uniform_real_distribution<double> unif(-1, 1);
    std::default_random_engine re;
    p = pp::vec(3*n);
    for (int i = 0; i < 3*n; ++i){if (i % n == 2){p[i] = std::abs(unif(re));} else{p[i] = unif(re);};}
    std::function<double(pp::vec)> loss = [&](pp::vec params){
        int dim = x.size();
        double sum = 0, value;
        for (int i = 0; i < dim; ++i){value = response(x[i], params) - y[i]; sum += value*value;}
        return sum;
    };
    std::tuple<double, pp::vec, int> res = newton_central(loss, p);
    p = std::get<1>(res);
    P = matrix(3*n, 1); P.set_row(0, p); P = P.reshape(3, n).T();
}