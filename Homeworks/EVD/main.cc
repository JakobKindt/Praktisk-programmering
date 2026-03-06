#include<iostream>
#include<cstdio>
#include<random>
#include"EVD.h"
#include<thread>
#include<fstream>

int main(int argc, char** argv){
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<> dist(2.0, 4.0);


    std::cout << "Part a \n";
    int N = 5;
    for (int i = 0; i < argc;i++){
        std::string arg = argv[i];
        if (arg == "-size" && i + 1 < argc){N = std::stoi(argv[++i]);}
    }
    std::cerr << "N = " << N << "\n";

    matrix C(N, N);
    
    for (int i = 0; i < C.ncols; ++i){
        for (int j = C.nrows - 1; j >= i; --j){
            C[i, j] = dist(gen);
            C[j, i] = C[i, j];
        }
    }
    C.print("random A = ");
    EVD A(C);
    A.V.print("V = ");

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






// int main(int argc, char** argv){
//     std::string outfile = "";
//     // std::cout << "Part b \n";
//     float rmax = 10;
//     float dr = 0.1;
//     bool make_dr = false;
//     bool make_rmax = false;
//     for (int i = 0; i < argc;i++){
//         std::string arg = argv[i];
//         if (arg == "-rmax" && i + 1 < argc){rmax = std::stod(argv[++i]);}
//         if (arg == "-dr" && i + 1 < argc){dr = std::stod(argv[++i]);}
// 		if(arg=="-output" && i+1 < argc) outfile=argv[i+1];
//         if (arg == "-make_dr"){make_dr = true;}
//         if (arg == "-make_rmax"){make_rmax = true;}
//     }
//     // std::cerr << "rmax = " << rmax << ", dr = " << dr << "\n";
    
//     std::ofstream myoutput(outfile);

//     int npoints = (int)(rmax/dr) - 1;
//     pp::vec r(npoints);
//     for(int i=0;i<npoints;i++)r[i]=dr*(i+1);
//     matrix H_raw(npoints,npoints);
//     for(int i=0;i<npoints - 1;i++){
//     H_raw[i,i]  =-2*(-0.5/dr/dr);
//     H_raw[i,i+1]= 1*(-0.5/dr/dr);
//     H_raw[i+1,i]= 1*(-0.5/dr/dr);
//     }
//     H_raw[npoints-1,npoints-1]=-2*(-0.5/dr/dr);
//     for(int i=0;i<npoints;i++)H_raw[i,i]+=-1/r[i];
//     EVD H(H_raw);
//     if (make_dr || make_rmax){std::cout << H.w[0] << "\n";}
//     if(myoutput.is_open() ){
//             for (int i = 0; i < H.V.ncols;++i){
//             myoutput << dr*i << " " << H.V.get_col(0)[i]/std::sqrt(dr) << " " << " " << H.V.get_col(1)[i]/std::sqrt(dr) <<  " " << H.V.get_col(2)[i]/std::sqrt(dr) <<  " " << H.V.get_col(3)[i]/std::sqrt(dr) << std::endl;
//             }
//         }
//     myoutput.close();
//     exit(EXIT_SUCCESS);
// return 0;
// }

// int main(int argc, char** argv){
//     std::mt19937 gen(std::random_device{}());
//     std::uniform_real_distribution<> dist(2.0, 4.0); 
//     int N = 5;
//     for (int i = 0; i < argc;i++){
//         std::string arg = argv[i];
//         if (arg == "-size" && i + 1 < argc){N = std::stoi(argv[++i]);}
//     }
    
//     matrix C(N, N);
    
//     for (int i = 0; i < C.ncols; ++i){
//         for (int j = C.nrows - 1; j >= i; --j){
//             C[i, j] = dist(gen);
//             C[j, i] = C[i, j];
//         }
//     }
//     EVD A(C, true);
// return 0;
// }