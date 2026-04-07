#include<iostream>
#include<cstdio>
#include"QUAD.h"
#include<fstream>
#include<cmath>
#include"vector.h"
inline double pi = 3.1415926535897932384626433;
double erf(double z, double acc = 0.001, double eps = 0.001){
        if (z < 0){return -erf(-z, acc, eps);}
        if (0 <= z && z <= 1){
            std::function<double(double)> gaus = [=](double x){return std::exp(-x*x);};
            return 2*integrate(gaus, 0., z, acc, eps)/std::sqrt(pi);
        }
        std::function<double(double)> f = [=](double t){
            if (t == 0.){return 0.;}
            double val = z + (1 - t)/t;
            return std::exp(-val*val)/t/t;
        };
        return 1. - 2.*integrate(f, 0., 1., acc, eps)/std::sqrt(pi);
    };

int main(){
    // PART A:
    std::cout << "Part A \n";
    double a = 0, b = 1;
    int ncalls2 = 0, ncalls4 = 0;

    std::function<double(double)> f1 = [] (double x){return std::sqrt(x);};
    std::function<double(double)> f2 = [&] (double x){++ncalls2; return 1/std::sqrt(x);};
    std::function<double(double)> f3 = [] (double x){return std::sqrt(1 - x*x);};
    std::function<double(double)> f4 = [&] (double x){++ncalls4; return std::log(x)/std::sqrt(x);}; // & is to capture ncalls as a reference.

    

    double I1 = integrate(f1, a, b);
    double I2 = integrate(f2, a, b);
    double I3 = integrate(f3, a, b);
    double I4 = integrate(f4, a, b);
    std::cout << "Measured integral of sqrt(x) from 0 to 1 is " << I1 << ". Theoretical is 2/3. \n"; 
    std::cout << "Measured integral of 1/sqrt(x) from 0 to 1 is " << I2 << ". Theoretical is 2. \n"; 
    std::cout << "Measured integral of sqrt(1 - x^2) from 0 to 1 is " << I3 << ". Theoretical is pi/4 \\simeq 0.78540. \n"; 
    std::cout << "Measured integral of ln(x)/sqrt(x) from 0 to 1 is " << I4 << ". Theoretical is -4. \n"; 

    
    std::cout << "Measured value of erf(1) is " << erf(1, 0.001, 0.001) << ". Theoretical is 0.84270079294971486934. \n";
    std::string outfile = "acc.txt";
    std::ofstream output_acc(outfile);
    pp::vec accs{1e-2, 1e-3, 1e-4, 1e-5, 1e-6, 1e-7, 1e-8, 1e-9};
    for (int i = 0; i < accs.size(); ++i){
        double acc = accs[i];
        double val = erf(1, acc, 0.);
        output_acc << acc << " " << val << " " << std::abs(val - 0.84270079294971486934) << "\n";
    }
    output_acc.close();

    // PART B
    ncalls2 = 0; ncalls4 = 0;
    double I2_CC = integrate_CC(f2, a, b);
    double I4_CC = integrate_CC(f4, a, b);
    

    std::cout << "\n Part B \n";
    std::cout << "Measured integral of 1/sqrt(x) from 0 to 1 using Clenshaw-Curtis is " << I2_CC << ". Theoretical is 2. \n"; 
    std::cout << "Measured integral of ln(x)/sqrt(x) from 0 to 1 using Clenshaw-Curtis is " << I4_CC << ". Theoretical is -4. \n"; 

    double inf = std::numeric_limits<double>::infinity();
    std::function<double(double)> exp = [=](double x){return std::exp(x);};
    std::function<double(double)> gauss = [=](double x){return std::exp(-x*x/2)/std::sqrt(2*pi);};
    double Iexp_CC = integrate_CC(exp, -inf, 0);
    double Igauss_CC = integrate_CC(gauss, -inf, inf);
    std::cout << "Implementation of infinities \n";
    std::cout << "Measured integral of exp(-x) from -\\infty to 0 using Clenshaw-Curtis is " << Iexp_CC << ". Theoretical is e \\simeq 1. \n"; 
    std::cout << "Measured integral of exp(-x**2/2)/\\sqrt(2*pi) from -\\infty to \\infty using Clenshaw-Curtis is " << Igauss_CC << ". Theoretical is e \\simeq 1. \n"; 

    std::cout << "Counting integrand evaluations \n";
    std::cout << "The value of integral of 1/sqrt(x) from 0 to 1 is " << I2_CC << ". In Python (scipy) is 1.9999999999999984.\n";
    std::cout << "ncalls for 1/sqrt(x) from 0 to 1 is " << ncalls2 << ". In Python (scipy) " << 231 << ".\n";
    std::cout << "The value of integral of ln(x)/sqrt(x) from 0 to 1 is " << I4_CC << ". In Python (scipy) is -4.000000000000085.\n";
    std::cout << "ncalls for ln(x)/sqrt(x) from 0 to 1 is " << ncalls4 << ". In Python (scipy) " << 315 << ".\n";
    // COMPARE NCALLS and value WITH PYTHON !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // Part c
    std::cout << "\n Part C \n";

    double Q1, Q2, Q3, Q4, err1, err2, err3, err4;
    std::tie(Q1, err1) = integrate_with_err(f1, a, b);
    std::tie(Q2, err2) = integrate_with_err(f2, a, b);
    std::tie(Q3, err3) = integrate_with_err(f3, a, b);
    std::tie(Q4, err4) = integrate_with_err(f4, a, b);
    std::cout << "Measured integral of sqrt(x) from 0 to 1 is " << Q1 << ". Theoretical is 2/3. Measured error is " << err1 << ". Actual difference from theoretical result is " << std::abs(Q1 - 2./3) << ". Thus measured err/actual err is " << err1/std::abs(Q1 - 2./3) << ".\n";
    std::cout << "Measured integral of 1/sqrt(x) from 0 to 1 is " << Q2 << ". Theoretical is 2. Measured error is " << err2 << ". Actual difference from theoretical result is " << std::abs(Q2 - 2.) << ". Thus measured err/actual err is " << err2/std::abs(Q2 - 2.) << ".\n";
    std::cout << "Measured integral of sqrt(1 - x^2) from 0 to 1 is " << Q3 << ". Theoretical is pi/4 \\simeq 0.78540. Measured error is " << err3 << ". Actual difference from theoretical result is " << std::abs(Q3 - pi/4) << ". Thus measured err/actual err is " << err3/std::abs(Q3 - pi/4) << ".\n";
    std::cout << "Measured integral of ln(x)/sqrt(x) from 0 to 1 is " << Q4 << ". Theoretical is -4. Measured error is " << err4 << ". Actual difference from theoretical result is " << std::abs(Q4 + 4.) << ". Thus measured err/actual err is " << err4/std::abs(Q4 + 4.) << ".\n";
    std::cout << "This means that the estimated error is larger than the actual error which is an intended feature and it is (almost) the same order of magnitude as the actual error. \n";
return 0;
}