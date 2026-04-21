#include<iostream>
#include<cstdio>
#include"QR-factorization.h"
#include"min.h"
#include<fstream>

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
    std::function<double(pp::vec)> D = [] (pp::vec x){
        double sum = 0;
        for (int i = 0; i < x.size(); ++i){
            sum += (x[0] - x[1])*(x[0] - x[1])/x[2]/x[2];
        }
        return sum;}; // The deviation function 
    
    pp::vec energy(0);
    pp::vec signal(0);
    pp::vec err(0);
    // var signal = new genlist<double>();
    // var error  = new genlist<double>();
    // var separators = new char[] {' ','\t'};
    // var options = StringSplitOptions.RemoveEmptyEntries;
    do{
        std::string line = Console.In.ReadLine();
        if (line == null){break;}
        std::string[] words = line.Split(seperatores, options);
        energy.push_back(double.Parse(word[0]));
        signal.push_back(double.Parse(words[1]));
        err.push_back(double.Parse(words[2]));
    }while(true);
    std::cout << energy << "\n";
    std::cout << signal << "\n";
    std::cout << err << "\n";
    // var energy = new genlist<double>();
    // var signal = new genlist<double>();
    // var error  = new genlist<double>();
    // var separators = new char[] {' ','\t'};
    // var options = StringSplitOptions.RemoveEmptyEntries;
    // do{
    //     std::string line = Console.In.ReadLine();
    //     if (line == null){break;}
    //     string[] words = line.Split(separators, options);
    //     energy.add(double.Parse(words[0]));
    //     signal.add(double.Parse(words[1]));
    //     error .add(double.Parse(words[2]));
    // }while(true);
return 0;
}