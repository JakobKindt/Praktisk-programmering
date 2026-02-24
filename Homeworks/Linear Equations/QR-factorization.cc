#include"QR-factorization.h"

pp::vec<double> QR::solve(pp::vec<double>& b){
    if (det() == 0){throw std::runtime_error("Determinant is 0");}
    pp::vec<double> v(b.size());
    v = Q.T()*b;
    v.print("v = ");
    pp::vec<double> x(R.nrows);
    for (int i = v.size() - 1; i >= 0;--i){
        double sum = 0;
        for (int j = i + 1; j < v.size();++j){
            sum += R[i, j]*x[j];
        }
        x[i] = (v[i] - sum)/R[i, i];
    }
    return x;
}

// pp::vec<double> QR::solve(pp::vec<double>& b){
//     if (det() == 0){throw std::runtime_error("Determinant is 0");}
//     matrix R_inv = identity(R.ncols);
//     R.print("R = ");
//     for (int i = 0; i < R.ncols; ++i){
//         for (int j = 0; j <= i; ++j){
//             for (int k = j + 1; k <= i;++k)
//             std::cout << i << ", " << j << ", " << R[j, i] << ", " << R[i, i] << "\n";
//             R_inv[j, i] = -R[j, i]/R[i, i];
//         }
//         R_inv[i, i] = 1/R[i, i];
//         std::cout << "\n";
//     }
//     R_inv.print("R_inv = ");
//     return R_inv*(Q.T()*b);
// }


// pp::vec<double> QR::solve(pp::vec<double>& b){
//     if (det() == 0){throw std::runtime_error("Determinant is 0");}
//     matrix R_inv = identity(R.ncols);
//     R.print("R = ");
//     for (int i = 0; i < R.ncols; ++i){
//         for (int j = 0; j <= i; ++j){
//             for (int k = j + 1; k <= i;++k)
//             std::cout << i << ", " << j << ", " << R[j, i] << ", " << R[i, i] << "\n";
//             R_inv[j, i] = -R[j, i]/R[i, i];
//         }
//         R_inv[i, i] = 1/R[i, i];
//         std::cout << "\n";
//     }
//     R_inv.print("R_inv = ");
//     return R_inv*(Q.T()*b);
// }

// pp::vec<double> QR::solve(pp::vec<double>& b){
//     if (det() == 0){throw std::runtime_error("Determinant is 0");}
//     matrix R_inv = identity(R.ncols);
//     R.print("R_inv = ");
//     for (int j = 0; j < R.nrows; ++j){
//         for (int i = 0; i < j; ++i){
//             // double sum = 0;
//             for (int k = i + 1; k <= j; ++k){
//                 std::cout << i << ", " << k << ", " << R[i, k] << ", " << R[k, i] << "\n";
//                 R_inv[i, j] = -R[i, k]*R_inv[k, j];
//             }
//             std::cout << "\n";
//             R_inv[i, j] /= R[j, j];
//         }
//         R_inv[j, j] = 1/R[j, j];
//     }
//     R_inv.print("R_inv = ");
//     return R_inv*(Q.T()*b);
// }



// pp::vec<double> QR::solve(pp::vec<double>& b){
//     if (det() == 0){throw std::runtime_error("Determinant is 0");}
//     matrix R_inv = identity(R.ncols);
//     R.print("R = ");
//     for (int i = 0; i < R.ncols; ++i){
//         for (int j = 0; j <= i; ++j){
//             std::cout << i << ", " << j << ", " << R[j, i] << ", " << R[i, i] << "\n";
//             R_inv[j, i] = -R[j, i]/R[i, i];
//         }
//         R_inv[i, i] = 1/R[i, i];
//         std::cout << "\n";
//     }
//     R_inv.print("R_inv = ");
//     return R_inv*(Q.T()*b);
// }

// pp::vec<double> QR::solve(pp::vec<double>& b){
//     if (det() == 0){throw std::runtime_error("Determinant is 0");}
//     matrix R_inv = identity(R.ncols);
//     R.print("R_inv = ");
//     for (int i = 0; i < R.ncols; ++i){
//         for (int j = 0; j < i; ++j){
//             // double sum = 0;
//             for (int k = i + 1; k <= j; ++k){
//                 R_inv[i, j] = -R[i, k]*R_inv[k, j];
//             }
//             R_inv[i, j] /= R[i, i];
//         }
//         R_inv[i, i] = 1/R[i, i];
//     }
//     R_inv.print("R_inv = ");
//     return R_inv*(Q.T()*b);
// }

double QR::det(){
    double a = 1;
    for (int i = 0; i < R.ncols;++i){
        a *= R[i, i];
    }
    return a;
};
// matrix inverse();