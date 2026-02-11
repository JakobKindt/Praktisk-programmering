#include<limits>
#include<iostream>
#include<cmath>
#include<iomanip>


bool approx(double a, double b, double acc = 1e-9, double eps = 1e-9) {
        double diff = std::abs(a - b);
        if (diff <= acc) return true;  // absolute tolerance
        double max_ab = std::max(std::abs(a), std::abs(b));
    return diff <= eps * max_ab;   // relative tolerance
}

int main(){
    float       f=1.0f; while((float)      (1.0f+f) != 1.0f){f/=2.0f;} f*=2.0f;
    double      d=1.0d; while((double)     (1.0d+d) != 1.0d){d/=2.0d;} d*=2.0d;
    long double l=1.0L; while((long double)(1.0L+l) != 1.0L){l/=2.0L;} l*=2.0L;
    std::cout << "My epsilon: \n";
    std::printf("      float eps=%g\n",f);
    std::printf("     double eps=%g\n",d);
    std::printf("long double eps=%Lg\n",l);
    std::cout << "Comparison to system\'s epsilon: \n";
    std::cout << std::numeric_limits<float>::epsilon() << "\n";
    std::cout << std::numeric_limits<double>::epsilon() << "\n";
    std::cout << std::numeric_limits<long double>::epsilon() << "\n";
    std::cout << "Conclusion: They are the same \n";
    std::cout << std::pow(2,-23) << "\n";
    std::cout << std::pow(2,-52) << "\n";
    std::cout << "\nPart 2: \n";
    double epsilon=std::pow(2,-52);
    double tiny=epsilon/2;
    double a=1+tiny+tiny;
    double b=tiny+tiny+1;
    std::cout << "a==b ? " << (a==b ? "true":"false") << "\n";
    std::cout << "a>1  ? " << (a>1  ? "true":"false") << "\n";
    std::cout << "b>1  ? " << (b>1  ? "true":"false") << "\n";
    std::cout << "\nPart 3: \n";
    double d1 = 0.1+0.1+0.1+0.1+0.1+0.1+0.1+0.1;
    double d2 = 8*0.1;
    std::cout << "d1==d2? " << (d1==d2 ? "true":"false") << "\n"; 
    std::cout << std::fixed << std::setprecision(17);
    std::cout << "d1=" << d1 << "\n";
    std::cout << "d2=" << d2 << "\n \n";

    std::cout << "With implemented approx function" << "\n";
    std::cout << "d1==d2? " << (approx(d1, d2) ? "true":"false") << "\n"; 
    std::cout << std::fixed << std::setprecision(17);
    std::cout << "d1=" << d1 << "\n";
    std::cout << "d2=" << d2 << "\n";
return 0;
}