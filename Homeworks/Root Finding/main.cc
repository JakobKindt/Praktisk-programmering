#include<iostream>
#include<cstdio>
#include"Root.h"
#include"QR-factorization.h"
#include"ODE.h"
#include<fstream>

matrix get_sols(std::function<pp::vec(pp::vec)> f){
    int N = 30;
    pp::vec xs = pp::linspace(-5, 5, N), start(2), x(2), x_temp{1, 1};
    matrix sols_temp(2, 50);
    bool new_sol = true;
    int s = 0;
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            start[0] = xs[i]; start[1] = xs[j];
            x = newton(f, start);
            for (int k = 0; k <= s; ++k){
                x_temp = sols_temp.get_row(k);
                if (approx(x, x_temp, 1e-3, 1e-10)){new_sol = false;}
            }
            if (new_sol){sols_temp.set_row(s, x); ++s;}
            new_sol = true;
        }
    }
    matrix sols(2, s);
    for (int i = 0; i < s; ++i){x_temp = sols_temp.get_row(i); sols.set_row(i, x_temp);}
    return sols;
}

void make_outfile(std::string& name, int n){
    pp::vec accs{1e-5, 1e-3, 1e-2, 0.1}, epss{1e-5, 1e-3, 1e-2, 0.1}, rmins{1e-5, 1e-3, 1e-2, 1e-1}, rmaxs{1, 3, 5, 10};
    double E = -0.6;
    std::function<pp::vec(double, pp::vec)> pend = [&](double r, pp::vec y){
        pp::vec dydx(2);
        dydx[0] = y[1];
        dydx[1] = -2/r*y[0] - 2*E*y[0];
        return dydx;
    };
    double r_min = 1e-9, r_max = 8, acc = 1e-2, eps = 1e-2;
    pp::vec y_init{r_min - r_min*r_min, 1 - 2*r_min};
    pp::vec start{-2}, x{1};
    std::function<pp::vec(pp::vec)> func = [&](pp::vec x){
        E = x[0];
        std::tuple<std::vector<double>, std::vector<pp::vec>> result = driver(pend, r_min, r_max, y_init, 0.125, acc, eps);
        std::vector<double> xs = std::get<0>(result);
        std::vector<pp::vec> ys = std::get<1>(result);
        pp::vec res{ys[(int)xs.size() - 1][0]};
        // for (int i = 0; i < (int)xs.size(); ++i){
        //     std::cout << xs[i] << ", " << ys[i][0] << ", " << ys[i][1] << "\n";
        // }
        return res;
    };
    std::string outfile = name;
    std::ofstream myoutput(outfile);
    for (int j = 0; j < 4; ++j){
        E = -0.6;
        if (n == 0){acc = accs[j];}
        if (n == 1){eps = epss[j];}
        if (n == 2){r_min = rmins[j];}
        if (n == 3){r_max = rmaxs[j];}
        x = newton(func, start, 1e-3);
        E = x[0];
        std::tuple<std::vector<double>, std::vector<pp::vec>> result = driver(pend, r_min, r_max, y_init);
        std::vector<double> xs = std::get<0>(result);
        std::vector<pp::vec> ys = std::get<1>(result);
        for (int i = 0; i < (int)xs.size(); ++i){
        myoutput << xs[i] << ", " << ys[i][0] << ", " << ys[i][1] << "\n";
        }
        myoutput << "\n\n";
    }
    myoutput.close();
}

int main(){
    // PART A:
    std::cout << "Part A \n";
    std::function<pp::vec(pp::vec)> f = [] (pp::vec x){
        pp::vec y(2); 
        y[0] = -2*(1. - x[0]) - 400.*x[0]*(x[1] - x[0]*x[0]); 
        y[1] = 200.*(x[1] - x[0]*x[0]); 
        return y;};
    
    std::function<pp::vec(pp::vec)> f2 = [] (pp::vec x){
        pp::vec y(2); 
        y[0] = 4.*x[0]*(x[0]*x[0] + x[1] - 11.) + 2.*(x[0] + x[1]*x[1] - 7.); 
        y[1] = 2.*(x[0]*x[0] + x[1] - 11.) + 4.*x[1]*(x[0] + x[1]*x[1] - 7.); 
        return y;};

    std::function<double(pp::vec)> D_f2 = [] (pp::vec x){
        double ddf_dxx = 12*x[0]*x[0] + 4*x[1] - 42;
        double ddf_dyy = 4*x[0] + 12*x[1]*x[1] - 26;
        double ddf_dxy = 4*(x[0] + x[1]);
        return ddf_dxx*ddf_dyy - ddf_dxy*ddf_dxy;};

    matrix sols = get_sols(f);
    sols.print("sols for Rosenbrock's valley = ");
    sols = get_sols(f2);
    sols.print("sols for Himmelblau's function = ");
    std::cout << "However, these also include the saddlepoints. The points which are actually local minima are:\n";
    pp::vec x_temp(2);
    double D;
    for (int i = 0; i < sols.ncols; ++i){
        x_temp = sols.get_row(i);
        D = D_f2(x_temp);
        if (D > 0){x_temp.print();}
    }
    std::cout << "Four of which are global minima where the function is 0. \n";


    // ------------------------------------------------------------------------------------------------------------------
    std::cout << "\nPart B \n";
    double E = 1;
    
    std::function<pp::vec(double, pp::vec)> pend = [&](double r, pp::vec y){
        pp::vec dydx(2);
        dydx[0] = y[1];
        dydx[1] = -2/r*y[0] - 2*E*y[0];
        return dydx;
    };
    double r_min = 1e-9, r_max = 8, acc = 1e-2, eps = 1e-2;
    pp::vec y_init{r_min - r_min*r_min, 1 - 2*r_min};

    std::function<pp::vec(pp::vec)> func = [&](pp::vec x){
        E = x[0];
        std::tuple<std::vector<double>, std::vector<pp::vec>> result = driver(pend, r_min, r_max, y_init, 0.125, acc, eps);
        std::vector<double> xs = std::get<0>(result);
        std::vector<pp::vec> ys = std::get<1>(result);
        pp::vec res{ys[(int)xs.size() - 1][0]};
        return res;
    };
    
    
    pp::vec start{-2}, x{1};
    x = newton(func, start, 1e-3);
    // ---------------------- Part C is an implementation for another algorithm to see that it works, simply use the upcoming line as x and compare the figures to see that they are identical
    // x = quasi_newton(func, start, 1e-3);
    E = x[0];
    std::tuple<std::vector<double>, std::vector<pp::vec>> result = driver(pend, r_min, r_max, y_init);
    std::vector<double> xs = std::get<0>(result);
    std::vector<pp::vec> ys = std::get<1>(result);

    std::string outfile = "wave_func.txt";
    std::ofstream myoutput(outfile);
    for (int i = 0; i < (int)xs.size(); ++i){
       myoutput << xs[i] << ", " << ys[i][0] << ", " << ys[i][1] << "\n";
    }
    myoutput.close();
    
    outfile = "conv_acc.txt"; make_outfile(outfile, 0);
    outfile = "conv_eps.txt"; make_outfile(outfile, 1);
    outfile = "conv_rmin.txt"; make_outfile(outfile, 2);
    outfile = "conv_rmax.txt"; make_outfile(outfile, 3);
    std::cout << "From the figures it becomes evident that rmin needs to be of the order of 1e-3, acc and eps of order 1e-2 and rmax of 10.\n";
return 0;
}