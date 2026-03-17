#include<iostream>
#include<cstdio>
#include<cmath>
#include"Splines.h"
#include<fstream>

// int main(int argc, char** argv){
int main(){
    int N = 100;
    double x = 0.5;
    pp::vec xs = pp::arange(0, 9, 0.5);
    pp::vec xs_plot = pp::linspace(0, 9, N);
    std::cout << "xs = " << xs << "\n";
    pp::vec ys(xs.size()), ys_plot(xs_plot.size()), Ys_plot(xs_plot.size());
    for (int i = 0; i < ys.size(); ++i){ys[i] = std::cos(xs[i]);}
    for (int i = 0; i < ys_plot.size(); ++i){ys_plot[i] = linterp(xs, ys, xs_plot[i]);}
    for (int i = 0; i < ys_plot.size(); ++i){Ys_plot[i] = linterpInteg(xs, ys, xs_plot[i]);}
    double integral = linterpInteg(xs, ys, x);
    std::cout << "Theoretical integral from antiderivative sin(x) is: " << std::sin(x) << ". \n";
    std::cout << "Calculated integral: " << integral << ". \n";

    std::string datafile = "data.txt";
    std::ofstream myoutput(datafile);

    for (int i = 0; i < xs_plot.size(); ++i){
        myoutput << xs_plot[i] << "\t" << ys_plot[i] << "\t" << Ys_plot[i];
        if (i < xs.size()){myoutput << "\t" << xs[i] << "\t" << ys[i];} 
        myoutput << "\n";
    }
    myoutput.close();
    
    exit(EXIT_SUCCESS);
return 0;
}