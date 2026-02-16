#include<iostream>
#include<cstdio>
#include"vec.h"
int main(){
    vec<double> v(1., 2., 3.);
    // vec<complex> v(std::complex(1., 0), std::complex(2., 2), std::complex(3., -1));
    vec<double> w(4., 5., 6.);
    // v.print();
    w.print();
    std::cout << "Is the same? " << (approx(v, w) ? "true" : "false") << "\n";
    std::cout << v << "\n";
    std::cout << w << "\n";
    double n = dot(v, w);
    std::cout << n << "\n";
    vec<double> k = v - 2;
    std::cout << k << "\n";
    w -= 2;
    std::cout << w << v << "\n";
    std::cout << dot(v, w) << "\n";
    std::cout << project(v, w) << "\n";
    std::cout << v.project(w) << "\n";
    std::cout << v.norm() << "\n";
    // std::cout << norm(v) << "\n";
    std::cout << w/2 << w*2 << "\n";
return 0;
}