#include"ANN.h"
#include"Splines.h" // For integration in part c
#include<random>

// std::uniform_real_distribution<double> unif(-1, 1);
// std::default_random_engine re;

pp::vec gradient(std::function<double(pp::vec)>& phi, pp::vec& x){
    double phi_x = phi(x);
    int dim = x.size();
    pp::vec g_phi(dim);
    for (int i = 0; i < dim; ++i){
        double dxi = (1 + std::abs(x[i]))*std::pow(2, -26);
        x[i] += dxi;
        g_phi[i] = (phi(x) - phi_x)/dxi;
        x[i] -= dxi;
    }
    return g_phi;
}

double ann::response(double x, pp::vec& q){/* return the response of the network to the input signal x */
    double sum = 0;
    for (int i = 0; i < n; ++i){sum += f((x - q[i])/q[n + i])*q[2*n + i];}
    return sum;
}

double ann::response(double x){return response(x, p);}
pp::vec ann::total_response(double x){
    pp::vec res(4);
    for (int i = 0; i < n; ++i){
        res[0] += f((x - p[i])/p[n + i])*p[2*n + i]; // f
        res[1] += F((x - p[i])/p[n + i])*p[2*n + i]*p[n + i]; // F
        res[2] += df((x - p[i])/p[n + i])*p[2*n + i]/p[n + i]; // df
        res[3] += ddf((x - p[i])/p[n + i])*p[2*n + i]/p[n + i]/p[n + i]; // ddf
    }
    return res;
}
void ann::train(pp::vec& x, pp::vec& y){ /* train the network to interpolate the given table {x,y} */
    std::uniform_real_distribution<double> unif(-1, 1);
    std::default_random_engine re;
    int max_patience = 500, patience = 0, epochs = 0, max_epochs = 100000; // I wish to add a scheduler of some sorts to reduce the learning rate.
    double best_loss, l;
    p = pp::vec(3*n);
    for (int i = 0; i < 3*n; ++i){if (i % n == 2){p[i] = std::abs(unif(re));} else{p[i] = unif(re);};}
    std::function<double(pp::vec)> loss = [&](pp::vec params){
        int dim = x.size();
        double sum = 0, value;
        for (int i = 0; i < dim; ++i){value = response(x[i], params) - y[i]; sum += value*value;}
        return sum;
    };

    // Training
    pp::vec g = gradient(loss, p); // Gradient of phi is calculated here
    best_loss = loss(p);
    for (int i = 0; i < max_epochs; ++i){
        ++epochs;
        g = gradient(loss, p); // Gradient of phi is calculated here
        p -= lr*g/g.norm();
        l = loss(p);
        if (l < best_loss){patience = 0; best_loss = l;}
        else{++patience;}
        if (patience == max_patience){patience = 0; lr = std::max(lr/2, 1e-8);}
        if(g.norm() < tol){std::cout << "tol reached after " << epochs << " epochs. \n"; break;}
    }
    P = matrix(3*n, 1); P.set_row(0, p); P.reshape(n, 3); P = P.T();
    std::cout << "final lr = " << lr << "\n";
}


//--------------------------------------------------------- Part c

double annc::response(double x, pp::vec& q){/* return the response of the network to the input signal x */
    double sum = 0;
    for (int i = 0; i < n; ++i){sum += f((x - q[i])/q[n + i])*q[2*n + i];}
    return sum;
}

double annc::response(double x){return response(x, p);}
double annc::dresponse(double x, pp::vec& q){
    double dsum = 0;
    for (int i = 0; i < n; ++i){dsum += df((x - q[i])/q[n + i])*q[2*n + i]/q[n + i];} // df
    return dsum;
}
double annc::dresponse(double x){return dresponse(x, p);}


pp::vec annc::total_response(double x, pp::vec& q){
    pp::vec res(4);
    for (int i = 0; i < n; ++i){
        res[0] += f((x - q[i])/q[n + i])*q[2*n + i]; // f
        res[1] += F((x - q[i])/q[n + i])*q[2*n + i]*q[n + i]; // F
        res[2] += df((x - q[i])/q[n + i])*q[2*n + i]/q[n + i]; // df
        res[3] += ddf((x - q[i])/q[n + i])*q[2*n + i]/q[n + i]/q[n + i]; // ddf
    }
    return res;
}

pp::vec annc::total_response(double x){return total_response(x, p);}


void annc::train(pp::vec& x, std::function<double(pp::vec&)>& Phi){ /* train the network to interpolate the given table {x,y} */
    std::uniform_real_distribution<double> unif(-1, 1);
    std::default_random_engine re;
    int max_patience = 500, patience = 0, epochs = 0, max_epochs = 100000; // I wish to add a scheduler of some sorts to reduce the learning rate.
    double best_loss, l;
    p = pp::vec(3*n);
    for (int i = 0; i < 3*n; ++i){if (i % n == 2){p[i] = std::abs(unif(re));} else{p[i] = unif(re);};}
    std::function<double(pp::vec)> loss = [&](pp::vec params){
        int dim = x.size();
        pp::vec res(4), z(4);
        double sum = 0;
        double value = response(c, params) - yc;
        sum += alpha*value*value; // Ensuring y(x) is correct
        value = dresponse(c, params) - dyc;
        sum += beta*value*value; // Ensuring dy/dx at c is correct

        for (int i = 0; i < dim; ++i){
            res = total_response(x[i], params); // Contains response, antiderivative of respons, derivative and double derivative in that order.
            z[0] = x[i]; z[1] = res[0]; z[2] = res[2]; z[3] = res[3];
            value = Phi(z);
            sum += value*value;
        }
        // CS, i.e. Cubic splines can be implemented by replacing the loop above by the outcommented lines. ChatGPT suggested doing the above for performance.
        // pp::vec ys(dim);
        // for (int i = 0; i < dim; ++i){
        //     res = total_response(x[i], params); // Contains response, antiderivative of respons, derivative and double derivative in that order.
        //     z[0] = x[i]; z[1] = res[0]; z[2] = res[2]; z[3] = res[3];
        //     value = Phi(z);
        //     ys[i] += value*value;
        // }
        // CS CS(x, ys); // Cubic splines from Homework Splines which has a integration method cinterpInteg using tabulated values xs, ys, i.e. x and y and calculates the integral from y[0] to some value z, i.e. b.
        // sum += CS.cinterpInteg(x, ys, x[x.size() - 1]); // Integral contribution
        return sum;
    };

    // Training
    pp::vec g = gradient(loss, p); // Gradient of phi is calculated here
    best_loss = loss(p);
    for (int i = 0; i < max_epochs; ++i){
        ++epochs;
        g = gradient(loss, p); // Gradient of phi is calculated here
        p -= lr*g/g.norm();
        l = loss(p);
        if (l < best_loss){patience = 0; best_loss = l;}
        else{++patience;}
        if (patience == max_patience){patience = 0; lr = std::max(lr/2, 1e-8);}
        if(g.norm() < tol){std::cout << "tol reached after " << epochs << " epochs. \n"; break;}
    }
    P = matrix(3*n, 1); P.set_row(0, p); P.reshape(n, 3); P = P.T();
    std::cout << "lr = " << lr << "\n";
}