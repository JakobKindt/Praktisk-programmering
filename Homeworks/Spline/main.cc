#include<iostream>
#include<cstdio>
#include<cmath>
#include"Splines.h"
#include<fstream>

int main(){
    std::cout << "Part a: \n";
    int N = 1000;
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
    pp::vec bs = QS.Q.get_row(0);
    pp::vec cs = QS.Q.get_row(1);
    bs.print("Calculated b = ");
    cs.print("Calculated c = ");
    std::cout << "Manually calculated b = {-0.08631, -0.56189, -0.89991, -1.01758, -0.88615, -0.53767, ...} \n";
    std::cout << "Manually calculated c = {-0.31705, -0.22535, -0.07845, 0.087614, 0.23232, 0.319951, ...} \n";

    std::cout << "Part c: \n";
    CS CS(xs, ys);
    for (int i = 0; i < ys_plot.size(); ++i){ys_plot[i] = CS.cinterp(xs, ys, xs_plot[i]);}
    for (int i = 0; i < ys_plot.size(); ++i){Ys_plot[i] = CS.cinterpInteg(xs, ys, xs_plot[i]);}
    integral = CS.cinterpInteg(xs, ys, x);
    std::cout << "Theoretical integral from antiderivative sin(x) is: " << std::sin(x) << ". \n";
    std::cout << "Calculated integral using cSpline: " << integral << ". \n";

    std::string datafile_c = "data_c.txt";
    std::ofstream myoutput_c(datafile_c);

    for (int i = 0; i < xs_plot.size(); ++i){
        myoutput_c << xs_plot[i] << "\t" << ys_plot[i] << "\t" << Ys_plot[i];
        if (i < xs.size()){myoutput_c << "\t" << xs[i] << "\t" << ys[i];} 
        myoutput_c << "\n";
    }
    myoutput_c.close();
    exit(EXIT_SUCCESS);
return 0;
}