#include<iostream>
#include<cstdio>
#include<cmath>
#include"Splines.h"
#include<fstream>

// int main(int argc, char** argv){
int main(){
    std::cout << "Part a: \n";
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
    std::cout << "Calculated integral using lSpline: " << integral << ". \n";

    std::string datafile_a = "data_a.txt";
    std::ofstream myoutput_a(datafile_a);

    for (int i = 0; i < xs_plot.size(); ++i){
        myoutput_a << xs_plot[i] << "\t" << ys_plot[i] << "\t" << Ys_plot[i];
        if (i < xs.size()){myoutput_a << "\t" << xs[i] << "\t" << ys[i];} 
        myoutput_a << "\n";
    }
    myoutput_a.close();
    

    std::cout << "Part b: \n";
    QS QS(xs, ys);
    for (int i = 0; i < ys_plot.size(); ++i){ys_plot[i] = QS.qinterp(xs, ys, xs_plot[i]);}
    for (int i = 0; i < ys_plot.size(); ++i){Ys_plot[i] = QS.qinterpInteg(xs, ys, xs_plot[i]);}
    integral = QS.qinterpInteg(xs, ys, x);
    std::cout << "Theoretical integral from antiderivative sin(x) is: " << std::sin(x) << ". \n";
    std::cout << "Calculated integral using qSpline: " << integral << ". \n";

    std::string datafile_b = "data_b.txt";
    std::ofstream myoutput_b(datafile_b);

    for (int i = 0; i < xs_plot.size(); ++i){
        myoutput_b << xs_plot[i] << "\t" << ys_plot[i] << "\t" << Ys_plot[i];
        if (i < xs.size()){myoutput_b << "\t" << xs[i] << "\t" << ys[i];} 
        myoutput_b << "\n";
    }
    myoutput_b.close();
    pp::vec bs = QS.Q.get_col(0);
    pp::vec cs = QS.Q.get_col(1);
    bs.print("Calculated b = ");
    cs.print("Calculated c = ");
    std::cout << "Manually calculated b = {-0.24483, -0.24483, -1.10429, -0.77397, -1.17359, -0.36643, ...} \n";
    std::cout << "Manually calculated c = {0, -0.85945, 0.330312, -0.39959, 0.807137, -0.02255, 0.992084, ...} \n";
    exit(EXIT_SUCCESS);
    
return 0;
}