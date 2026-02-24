#include"QR-factorization.h"

pp::vec<double> QR::solve(pp::vec<double>& b){
    if (det() == 0){throw std::runtime_error("Determinant is 0");}
    pp::vec<double> v(b.size());
    v = Q.T()*b;
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


matrix QR::inverse(){
    if (det() == 0){throw std::runtime_error("Determinant is 0");}
    matrix R_inv = identity(R.ncols);
    for (int i = R.ncols - 1; i >= 0; --i){
        R_inv[i, i] = 1/R[i, i];
        for (int j = i - 1; j >= 0; --j){
            for (int k = j + 1; k <= i;++k){
            R_inv[j, i] -= R_inv[k, i]*R[j, k]/R[j, j];
            }
        }
    }
    return R_inv*Q.T();
}

double QR::det(){
    double a = 1;
    for (int i = 0; i < R.ncols;++i){
        a *= R[i, i];
    }
    return a;
};
// matrix inverse();