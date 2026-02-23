#include<iostream>
#include<cstdio>
// #include"vec.h"
#include"matrix.h"
int main(){
    matrix B(2, 3);
    pp::vec<double> v{1, 2, 3};
    // pp::vec<double> v{1, 2};
    v.print("v = ");
    B = matrix({{1., 2., 3.}, {4., 5., 6.}});
    matrix C{{1.5, 2.5, 3.5}, {4.5, 5.5, 6.5}};
    matrix B_T = B.T();
    B.print("B = ");
    C.print("C = ");
    B_T.print("B.T = ");
    matrix D = C - 2.5;
    D.print("C*B_T = ");
    std::cout << approx(C, C) << "\n"; 
    pp::vec<double> w = B*v;
    w.print("w = ");
return 0;
}

// int main(){
//     matrix B(2, 3);
//     B = matrix({{1., 2., 3.}, {4., 5., 6.}});
//     matrix C{{1.5, 2.5, 3.5}, {4.5, 5.5, 6.5}};
//     matrix B_T = B.T();
//     B.print("B = ");
//     C.print("C = ");
//     B_T.print("B.T = ");
//     matrix D = C - 2.5;
//     D.print("C*B_T = ");
//     C.reshape(1, 6);
//     C.print("C reshaped to 1, 6 = ");   
//     matrix E = B.reshape(6, 1);
//     E.print("B reshaped to 6, 1 = ");
// return 0;
// }