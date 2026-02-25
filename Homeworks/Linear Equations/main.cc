#include<iostream>
#include<cstdio>
#include<random>
#include<cmath>
#include"QR-factorization.h"

int main(int argc, char** argv){
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

// PART C IS DONE SEPERATELY SINCE WE ARE TIMING THE PROCESS AND DO NOT WANT TO DO PART A AND B FOR NO REASON - JUST EXCLUDE THE PREVIOUS MAIN AND INCLUDE THE FOLLOWING MAIN INSTEAD.
// int main(int argc, char** argv){
//     std::uniform_real_distribution<> dist(2.0, 4.0); 
//     std::default_random_engine re;
//     std::mt19937 gen(re());


//     std::cout << "Part c \n";
//     int N = 1;
//     for (int i = 0; i < argc;i++){
//         std::string arg = argv[i];
//         if (arg == "-size" && i + 1 < argc){N = std::stoi(argv[++i]);}
//     }
//     std::cerr << "N = " << N << "\n";

//     matrix C(N, N);
//     for (int i = 0; i < C.nrows*C.ncols; ++i){
//         C.cols[i] = dist(re);
//     }

//     QR A{C};
// return 0;
// }