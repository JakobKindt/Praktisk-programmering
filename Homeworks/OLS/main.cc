#include<iostream>
#include<cstdio>
// #include"QR-factorization.h"
#include"OLS.h"
#include<fstream>
#include<cmath>


// int main(int argc, char** argv){
int main(){
    std::string outfile = "fitting_parameters.txt";
    pp::vec x{1, 2, 3, 4, 6, 9, 10, 13, 15}, y{117, 100, 88, 72, 53, 29.5, 25.2, 15.2, 11.1}, dy{6, 5, 4, 4, 4, 3, 3, 2, 2};
    pp::vec lny(y.size());
    for (int i = 0; i < lny.size(); ++i){lny[i] = std::log(y[i]);};
    pp::vec dlny = dy/y;
    std::vector<std::function<double(double)>> fs {
        [](double z) { return 1 + 0*z; }, // ln(a). The 0*z is simply so that z is used for -Wall - Wextra
        [](double z) { return -z; } // -lambda*t
	};
    OLS::lsfit A(fs, x, lny, dlny);
    A.c.print("Optimal parameters for ln(a) and lambda respectively are");
    A.Sigma.print("The covarience matrix for ln(a) and lambda is");
    std::cout << "Uncertainty on ln(y) is dy/y since ln'(y) = 1/y, so (dln(y))^2 = (dy*ln'(y))^2 = (dy/y)^2 as wanted. \n";
    std::cout << "Halflife (ln(2)/lambda) is equal to " << std::log(2)/A.c[1] << " days. Modern value is 3.6316(23) days. Source is: https://chemlin.org/isotope/radium-224 \n";
    std::cout << "Uncertainty of halflife is by the law of accumulation given as (ln(2)*dlambda/lambda**2) which equal to " << std::log(2)*std::sqrt(A.Sigma[1, 1])/(A.c[1]*A.c[1]) << " days. \n";
    std::cout << "This means that the experiment is " << (std::log(2)/A.c[1] - 3.6316)/(std::log(2)*std::sqrt(A.Sigma[1, 1])/(A.c[1]*A.c[1])) << " standard deviations away from the modern result. \n";
    
    std::ofstream myoutput(outfile);

    for (int i = 0; i < A.c.size(); ++i){
        myoutput << A.c[i] << " " << std::sqrt(A.Sigma[i, i]) << "\n";
    }
    myoutput.close();
    std::string datafile = "data.txt";
    std::ofstream mydata(datafile);

    for (int i = 0; i < y.size(); ++i){
        mydata << x[i] << "\t" << y[i] << "\t" << dy[i] << "\t" << lny[i] << "\t" << dlny[i] << "\n";
    }
    mydata.close();
    exit(EXIT_SUCCESS);
return 0;
}