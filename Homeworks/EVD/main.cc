#include<iostream>
#include<cstdio>
#include<random>
#include"EVD.h"

int main(int argc, char** argv){
    std::uniform_real_distribution<> dist(2.0, 4.0); 
    std::default_random_engine re;
    std::mt19937 gen(re());


    std::cout << "Part a \n";
    int N = 5;
    for (int i = 0; i < argc;i++){
        std::string arg = argv[i];
        if (arg == "-size" && i + 1 < argc){N = std::stoi(argv[++i]);}
    }
    std::cerr << "N = " << N << "\n";

    matrix C(N, N);
    C.print("C=");
    
    for (int i = 0; i < C.ncols; ++i){
        for (int j = C.nrows - 1; j >= i; --j){
            C[i, j] = dist(re);
            C[j, i] = C[i, j];
        }
    }
    C.print("random A = ");

    std::cerr << "calling EVD...\n";
    EVD A(C);
    std::cerr << "...EVD done\n";
    
    A.V.print();

    (A.V.T()*A.V).print("V.T*V = ");
    (A.V*A.V.T()).print("V*V.T = ");
    (A.V.T()*C*A.V).print("V.T*A*V = ");
    matrix D = identity(N);
    for (int i = 0; i < N; ++i){
        D[i, i] = A.w[i];
    }
    D.print("D = ");
    (A.V*D*A.V.T()).print("V*D*V.T = ");
return 0;
}