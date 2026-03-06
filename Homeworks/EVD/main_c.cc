#include<iostream>
#include<cstdio>
#include<random>
#include"EVD.h"
#include<thread>
#include<fstream>

int main(int argc, char** argv){
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<> dist(2.0, 4.0); 
    int N = 5;
    for (int i = 0; i < argc;i++){
        std::string arg = argv[i];
        if (arg == "-size" && i + 1 < argc){N = std::stoi(argv[++i]);}
    }
    
    matrix C(N, N);
    
    for (int i = 0; i < C.ncols; ++i){
        for (int j = C.nrows - 1; j >= i; --j){
            C[i, j] = dist(gen);
            C[j, i] = C[i, j];
        }
    }
    EVD A(C, true);
return 0;
}