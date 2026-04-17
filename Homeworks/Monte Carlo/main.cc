#include<iostream>
#include<cstdio>
#include"MC.h"
#include<cmath>
#include"fstream"
inline double pi = 3.1415926535897932384626433;

int main(){
    // PART A:
    std::cout << "Part A \n";
    pp::vec B{1, 2, 3};
    std::function<double(pp::vec)> f = [] (pp::vec x){return x[1];};
    std::function<double(pp::vec)> f3 = [=] (pp::vec x){
        pp::vec v = x*x/B/B;
        if (v[0] + v[1] + v[2] <= 1){return 1;}
        return 0;
    };
    pp::vec A = -B;
    pp::vec a{0, 0}, b{2*pi, 1};
    pp::vec Ns{1e3, 5e3, 1e4, 5e4, 1e5, 5e5, 1e6, 5e6, 1e7};
    // pp::vec Ns{1e2, 1e3, 1e4};
    pp::vec res(2);
    int s = Ns.size();

    // Investigation of if err goes as 1/sqrt(N)
    std::string outfile = "err.txt";
    std::ofstream myoutput(outfile);
    for (int i = 0; i < s; ++i){
        res = MC(f, a, b, Ns[i]);
        myoutput << Ns[i] << " " << res[0] << " " << res[1] << " " << std::abs(pi - res[0]) << "\n";
    }
    myoutput.close();


    res = MC(f3, A, B, 1e6);
    std::cout << "Measured integral of volume ellipsoid with semi-axis a = 1, b = 2 and c = 3: " << res[0] << ". With an error of: " << res[1] << ". Theoretical is " << 4/3.*pi*B[0]*B[1]*B[2] << ".\n";
    std::cout << "Thus, the percensive deviation is " << (res[0] - 4/3.*pi*B[0]*B[1]*B[2])/(4/3.*pi*B[0]*B[1]*B[2])*100 << "% with an error of: " << res[1]/(4/3.*pi*B[0]*B[1]*B[2])*100 << "%.\n";
    std::cout << "|measured - theory|/(estimated err) = " << std::abs(res[0] - 4/3.*pi*B[0]*B[1]*B[2])/res[1] << ". \n";
    std::cout << "|measured - theory| = " << std::abs(res[0] - 4/3.*pi*B[0]*B[1]*B[2]) << ". \n";

    // ---------------------------------------------------------------------------------------------------------------------------
    std::cout << "\n\nPart B \n"; 
    
    std::function<double(pp::vec)> f2 = [=](pp::vec x){return 1/(1 - std::cos(x[0])*std::cos(x[1])*std::cos(x[2]))/pi/pi/pi;
    };

    pp::vec vec_0{0, 0, 0};
    std::function<double(pp::vec)> f4 = [=](pp::vec x){
        if (!approx(x, vec_0)){return 1/(1 - std::cos(x[0])*std::cos(x[1])*std::cos(x[2]))/pi/pi/pi;}
        else{return 0.;}
    };

    a = pp::vec{0, 0, 0}; b = pp::vec{pi, pi, pi};
    res = MC(f2, a, b, 1e6);
    std::cout << "Integration via. lcg \n";
    std::cout << "Measured integral of (1 - cos(x)cos(y)cos(z))^-1/pi^3 from 0 to pi in all dimensions is: " << res[0] << ". With an error of: " << res[1] << ". Theoretical is 1.3932039296856768591842462603255. \n";
    std::cout << "Thus, the percensive deviation is " << (res[0] - 1.3932039296856768591842462603255)/1.3932039296856768591842462603255*100 << "% with an error of: " << res[1]/1.3932039296856768591842462603255*100 << "%.\n";
    std::cout << "|measured - theory|/(estimated err) = " << std::abs(res[0] - 1.3932039296856768591842462603255)/res[1] << ". \n";
    std::cout << "|measured - theory| = " << std::abs(res[0] - 1.3932039296856768591842462603255) << ". \n";


    res = MC(f2, a, b, 1e6, 1);
    std::cout << "\nIntegration via. built-in generator \n";
    std::cout << "Measured integral of (1 - cos(x)cos(y)cos(z))^-1/pi^3 from 0 to pi in all dimensions is: " << res[0] << ". With an error of: " << res[1] << ". Theoretical is 1.3932039296856768591842462603255. \n";
    std::cout << "Thus, the percensive deviation is " << (res[0] - 1.3932039296856768591842462603255)/1.3932039296856768591842462603255*100 << "% with an error of: " << res[1]/1.3932039296856768591842462603255*100 << "%.\n";
    std::cout << "|measured - theory|/(estimated err) = " << std::abs(res[0] - 1.3932039296856768591842462603255)/res[1] << ". \n";
    std::cout << "|measured - theory| = " << std::abs(res[0] - 1.3932039296856768591842462603255) << ". \n";

    res = QMC(f2, a, b, 1e6, 3);
    std::cout << "\nIntegration via. quasi random sequence does not work for the function directly because sometimes I get too close to 0. The results are: \n";
    std::cout << "Measured integral of (1 - cos(x)cos(y)cos(z))^-1/pi^3 from 0 to pi in all dimensions is: " << res[0] << ". With an error of: " << res[1] << ". Theoretical is 1.3932039296856768591842462603255. \n";
    std::cout << "Thus, the percensive deviation is " << (res[0] - 1.3932039296856768591842462603255)/1.3932039296856768591842462603255*100 << "% with an error of: " << res[1]/1.3932039296856768591842462603255*100 << "%.\n";
    std::cout << "|measured - theory|/(estimated err) = " << std::abs(res[0] - 1.3932039296856768591842462603255)/res[1] << ". \n";
    std::cout << "|measured - theory| = " << std::abs(res[0] - 1.3932039296856768591842462603255) << ". \n";

    res = QMC(f4, a, b, 1e6, 3);
    std::cout << "\nHowever, if we alter the function to be 0 if we are approximately at 0, we get the following results of integration via. quasi random sequence \n";
    std::cout << "Measured integral of (1 - cos(x)cos(y)cos(z))^-1/pi^3 from 0 to pi in all dimensions is: " << res[0] << ". With an error of: " << res[1] << ". Theoretical is 1.3932039296856768591842462603255. \n";
    std::cout << "Thus, the percensive deviation is " << (res[0] - 1.3932039296856768591842462603255)/1.3932039296856768591842462603255*100 << "% with an error of: " << res[1]/1.3932039296856768591842462603255*100 << "%.\n";
    std::cout << "|measured - theory|/(estimated err) = " << std::abs(res[0] - 1.3932039296856768591842462603255)/res[1] << ". \n";
    std::cout << "|measured - theory| = " << std::abs(res[0] - 1.3932039296856768591842462603255) << ". \n";

    std::cout << "\n\nThus, the best method is plain MC using the built-in random number generator\n";


    std::cout << "\nI also investigated how the error scales here \n";
    a = pp::vec{0, 0}; b = pp::vec{2*pi, 1};
    res = pp::vec(2);

    // Investigation of if err goes as 1/sqrt(N)
    std::string outfile_B = "quasi_err.txt";
    std::ofstream myoutput_B(outfile_B);
    for (int i = 0; i < s; ++i){
        res = QMC(f, a, b, Ns[i], 2); // last number dictates how many different sequences should be compared.
        myoutput_B << Ns[i] << " " << res[0] << " " << res[1] << " " << std::abs(pi - res[0]) << "\n";
    }
    myoutput_B.close();
    std::cout << "Uncertainties with this method has been made smaller by a factor of roughly 2 (10 times faster with built-in generator). However, now the estimated errors are generally lower than the actual errors which is probably because the estimated errors are systematic error and not the actual error of the method.\n";
    std::cout << "The error seemingly still follows a somewhat 1/sqrt(N) dependence but convergence faster. The 1/sqrt(N) dependence is clearer when the built-in random number generator is used. \n";

    // ---------------------------------------------------------------------------------------------------------------------------
    std::cout << "\n\nPart C \n";
    res = SMC(f, a, b, 1e6, 1e3);
    std::cout << "Measured integral of unit circle: " << res[0] << ". With an error of: " << res[1] << ". Theoretical is pi \\simeq 3.1415926535897932384626433. \n";
    std::cout << "Thus, the percensive deviation is " << (res[0] - pi)/pi*100 << "% with an error of: " << res[1]/pi*100 << "%.\n";
    std::cout << "|measured - theory|/(estimated err) = " << std::abs(res[0] - pi)/res[1] << ". \n";
    std::cout << "|measured - theory| = " << std::abs(res[0] - pi) << ". \n";
    
return 0;
}