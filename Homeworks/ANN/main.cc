#include<iostream>
#include"ANN.h"
#include<fstream>

int main(){
    // PART A:
    std::cout << "Part A and B \n";
    std::function<double(double)> f = [] (double x){return std::cos(5*x - 1)*std::exp(-x*x);}; // Test function
    int N = 60;
    pp::vec xs_train = pp::linspace(-1, 1 + 2./N, N), xs_plot = pp::linspace(-3., 3., N);
    pp::vec ys_train(xs_train.size()), ys_plot(xs_plot.size());
    for (int i = 0; i < xs_train.size(); ++i){ys_train[i] = f(xs_train[i]);}
    ann B(4, 1e-1, 1e-1); // Neurons, initial learning rate and threshold for norm of gradient before stopping prematurely
    B.train(xs_train, ys_train);
    std::string outfile = "data.txt";
    std::ofstream myoutput(outfile);
    double x, y;
    pp::vec res(4);
    for (int i = 0; i < xs_plot.size(); i++){
        x = xs_plot[i];
        res = B.total_response(x); // f, F, df, ddf
        myoutput << x << " " << res[0] << " " << res[1] << " " << res[2] << " " << res[3] << "\n";
    }
    myoutput << "\n\n";
    for (int i = 0; i < xs_train.size(); i++){
        x = xs_train[i];
        y = ys_train[i];
        myoutput << x << " " << y << "\n";
    }
    myoutput.close();
    // ------------------------------------------------------------------------------------------------------------------------------------------------
    std::cout << "\n\nPart C \n";

    N = 120;
    xs_plot = pp::linspace(-1, 1, N);
    xs_train = pp::linspace(-1, 1 + 2./N, N);
    std::function<double(pp::vec&)> Phi = [](pp::vec& z){ // z[0] = x, z[1] = y, z[2] = y', z[3] = y''
        return z[3] - 3*z[2] + 2*z[1] + z[0]; // Theoretical solution c_1e^2x + c_2e^3x - x/6 - 5/36
    };
    annc C(4, 1e-2, 1e-2, 0, 1./2, 0); // Neurons, initial learning rate and threshold for norm of gradient before stopping prematurely // int n, double lr, double tol, double c, double yc, double dyc
    C.train(xs_train, Phi);

    std::string outfile2 = "data2.txt";
    std::ofstream myoutput2(outfile2);
    for (int i = 0; i < xs_plot.size(); i++){
        x = xs_plot[i];
        res = C.total_response(x); // f, F, df, ddf
        myoutput2 << x << " " << res[0] << " " << res[1] << " " << res[2] << " " << res[3] << "\n";
    }
    myoutput2 << "\n\n";
    xs_train = pp::linspace(-0.5, 0.5 + 2./N, N); // Smaller training set
    annc D(4, 1e-2, 1e-2, 0, 1./2, 0); // Neurons, initial learning rate and threshold for norm of gradient before stopping prematurely // int n, double lr, double tol, double c, double yc, double dyc
    D.train(xs_train, Phi);
    for (int i = 0; i < xs_plot.size(); i++){
        x = xs_plot[i];
        res = D.total_response(x); // f, F, df, ddf
        myoutput2 << x << " " << res[0] << " " << res[1] << " " << res[2] << " " << res[3] << "\n";
    }
    myoutput2.close();
    std::cout << "After investigating a bit it turns out that the initial (random) guess for the optimizable parameters have a big influence. So does what interval we are looking at and the number of nodes, so this method is rather unstable when it comes to solving differential equations with only one (or two) initial conditions. \n";
return 0;
}
