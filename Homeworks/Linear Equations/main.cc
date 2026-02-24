#include<iostream>
#include<cstdio>
// #include"vec.h"
// #include"matrix.h"
#include"QR-factorization.h"
int main(){
    pp::vec<double> b{2, 5, 1, 2};
    matrix C{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 13}};
    // matrix C{{12, -51, 4}, {6, 167, -68}, {-4, 24, -41}, {1, 2, 3}};
    // matrix C{{1, 0, 0}, {0, 1, 0}, {0, 0, 2}};
    C.print("C = ");
    QR A{C};
    A.Q.print("Q = ");
    A.R.print("R = ");
    // double n = A.det();
    // std::cout << n << "\n";
    pp::vec<double> x = A.solve(b);
    x.print();
return 0;
}