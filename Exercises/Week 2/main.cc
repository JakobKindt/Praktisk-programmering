#include<iostream>
#include<cstdio>
// #include<vector>
#include"vec.h"
int main(){
    vec v(1., 2., 3.);
    v.print();
    vec w(4., 6., 8.);
    w.print();
    double a = 2;
    vec s = a - v;
    s.print();
    w /= a;
    w.print();
    w += 1.;
    w.print();
    w -=2.;
    w.print();
    // if (approx(v, w)){
    //     std::cout << "True" << "\n";
    // }
    std::cout << v << "\n";
return 0;
}