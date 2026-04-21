#include<iostream>
#include<cstdio>
#include"QR-factorization.h"
#include"min.h"
#include <fstream>
#include <sstream>

int main(){
    // PART A:
    std::cout << "Part A \n";
    std::function<double(pp::vec)> RV = [] (pp::vec x){return (1. - x[0])*(1. - x[0]) + 100.*(x[1] - x[0]*x[0])*(x[1] - x[0]*x[0]);}; // Rosenbrock's valley function
    
    std::function<double(pp::vec)> Hf = [] (pp::vec x){return (x[0]*x[0] + x[1] - 11.)*(x[0]*x[0] + x[1] - 11.) + (x[0] + x[1]*x[1] - 7.)*(x[0] + x[1]*x[1] - 7.);}; // Himmelblau's function
    
    pp::vec start{20, 20};
    std::tuple<double, pp::vec, int> min = newton(RV, start);
    std::cout << "Starting at " << start << ", a found minimum of Rosenbrock's valley function is " << std::get<0>(min) << " at " << std::get<1>(min) << " using " << std::get<2>(min) << " counts.\n";
    min = newton(Hf, start);
    std::cout << "Starting at " << start << ", a found minimum of Himmelblau's function is " << std::get<0>(min) << " at " << std::get<1>(min) << " using " << std::get<2>(min) << " counts.\n";
    std::cout << "Both of the functions do have a theoretical global minimum of 0. For the Rosenbrock's valley function is occurs at (1, 1) and for the Himmelblau's function it occurs at (3, 2), (-2.805, 3.1313), (-3.779, -3.283) and (3.584, -1.848).\n";

    // ----------------------------------------------
    std::cout << "\n\nPart B \n";
    std::ifstream file("exp_data.txt");
    std::string line;
    pp::vec energies(0);
    pp::vec signals(0);
    pp::vec errs(0);

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        double e, s, er;
        if (iss >> e >> s >> er) {
            energies.push_back(e);
            signals.push_back(s);
            errs.push_back(er);
        }
    }


    double E;
    std::function<double(pp::vec)> F = [&] (pp::vec x){return x[2]/((E - x[0])*(E - x[0]) + x[1]*x[1]/4.);}; // The Breit-Wigner function
    std::function<double(pp::vec)> D = [&] (pp::vec x){
        double sum = 0;
        for (int i = 0; i < energies.size(); ++i){
            E = energies[i];
            sum += (F(x) - signals[i])*(F(x) - signals[i])/errs[i]/errs[i];
        }
        return sum;}; // The deviation function 
    
    
    // start = pp::vec{125, 4, 12};
    start = pp::vec{125, 4, 15};
    min = newton(D, start, 1e-3, 10000);
    std::cout << "Starting at " << start << ", a found minimum of the deviation function is " << std::get<0>(min) << " at " << std::get<1>(min) << " (mass, gamma, A) using " << std::get<2>(min) << " counts.\n";
    std::cout << "Note that the method is not that stable since if we change the starting condition slightly, we get: \n";
    start = pp::vec{130, 4, 15};
    min = newton(D, start, 1e-3, 10000);
    std::cout << "Starting at " << start << ", a found minimum of the deviation function is " << std::get<0>(min) << " at " << std::get<1>(min) << " (mass, gamma, A) using " << std::get<2>(min) << " counts (i.e. max counts).\n";
    
return 0;
}