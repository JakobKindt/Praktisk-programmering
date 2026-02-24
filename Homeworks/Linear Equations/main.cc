#include<iostream>
#include<cstdio>
#include<random>
#include<cmath>
// #include"vec.h"
// #include"matrix.h"
#include"QR-factorization.h"

// int main()
// {
//     // Declaring the upper and lower
//     // bounds
//     double lower_bound = 0;
//     double upper_bound = 100;

//     uniform_real_distribution<double> unif(lower_bound,
//                                            upper_bound);

//     default_random_engine re;

//     // Getting a random double value
//     double random_double = unif(re);

//     cout << random_double << endl;

//     return 0;
// }

int main(){
    
    // matrix C{{1, 2, 3}, {0, 5, 6}, {0, 0, 10}};
    std::uniform_real_distribution<> dist(2.0, 4.0); 
    std::default_random_engine re;
    std::mt19937 gen(re());
    double q = dist(re);
    
    std::cout << q << "\n";
    
    matrix C(3, 4);
    for (int i = 0; i < C.nrows*C.ncols; ++i){
        C.cols[i] = dist(re);
    }
    pp::vec<double> b(C.ncols);
    for (int i = 0; i < b.size(); ++i){
        b[i] = dist(re);
    }

    QR A{C};
    C.print("A = ");
    A.Q.print("Q = ");
    A.R.print("R = ");


    matrix E = A.Q.T()*A.Q;
    E.print("Q^T*Q = ");
    (A.Q*A.R).print("Q*R = ");
    
    pp::vec<double> x = A.solve(b);
    b.print("b = ");
    x.print("x = ");
    (C*x).print("A*x = ");


    std::cout << "Part b \n";

    matrix D(3, 3);
    for (int i = 0; i < D.nrows*D.ncols; ++i){
        D.cols[i] = dist(re);
    }
    QR G{D};
    D.print("A = ");
    matrix B(D.nrows, D.ncols);
    B = G.inverse();
    B.print("A inverse = ");
    (D*B).print("A*B = ");
return 0;
}