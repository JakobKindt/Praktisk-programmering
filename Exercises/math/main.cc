#include<cmath>
#include<complex>
#include<iostream>
#include"sfuns.h"


using complex=std::complex<double>;
constexpr double  π = 3.14159265358979324;
constexpr double  E = 2.71828182845904523;
constexpr complex I = complex(0,1);
int main(){
    std::cout << "log(I)=" << std::log(I)   << "\t Exact result: 1.5707963267948i"<<"\n";
    std::cout << "   I^I=" << std::pow(I,I) << "\t Exact result: 0.20787957635076"<<"\n";
    std::cout << "   π^I=" << std::pow(π,I) << "\t Exact result: 0.41329211 + 0.91059849i"<<"\n";
    std::cout << "   E^I=" << std::pow(E,I) << "\t Exact result: 0.5403023058681 + 0.8414709848i"<<"\n";
    for (double i = 1; i<= 10; i++){
        std::cout << "\t gamma(" << i <<") = " << sfuns::fgamma(i) <<"\n";
    }
    std::cout << "Exact results (in order) are: 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880";
    std::cout << "Implementation of ln(gamma) and comparison to actual gamma to show overflowing issue \n"; 
    for (double i = 170; i<= 175; i++){
        std::cout << "\t gamma(" << i <<") = " << sfuns::fgamma(i) <<"\n";
        std::cout << "\t ln(gamma(" << i <<")) = " << sfuns::lnfgamma(i) <<"\n \n";
    }
return 0;
}