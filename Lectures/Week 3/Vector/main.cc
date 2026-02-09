#include<iostream>
#include<cstdio>
#include"vec.h"
int main(){
    vec v(1., 2., 3.);
    vec w(4., 5., 6.);
    w.print();
    if (approx(v, w)){
        std::cout << "True" << "\n";
    }
    std::cout << v << "\n";
    std::cout << w << "\n";
    double n = dot(v, w);
    std::cout << n << "\n";
    vec k = project(v, w);
    std::cout << k << "\n";
    vec q = v.project(w);
    std::cout << q << "\n";
return 0;
}