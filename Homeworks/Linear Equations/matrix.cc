#include"matrix.h"

bool dimension_check(const matrix& A, const matrix& B){
    if (A.cols_size() != B.cols_size() && A.rows_size() != B.rows_size()){throw std::runtime_error("Colomns and rows mismatch, cols = " + std::to_string(A.cols_size()) + ", " + std::to_string(B.cols_size()) + ", rows = " + std::to_string(A.rows_size()) + ", " + std::to_string(B.rows_size()) + ". \n");};
    if (A.cols_size() != B.cols_size()){throw std::runtime_error("Colomns mismatch, cols = " + std::to_string(A.cols_size()) + ", " + std::to_string(B.cols_size()) + ". \n");};
    if (A.rows_size() != B.rows_size()){throw std::runtime_error("Rows mismatch, rows = " + std::to_string(A.rows_size()) + ", " + std::to_string(B.rows_size()) + ". \n");};
    return true;
}

matrix& matrix::operator*=(const double a){for(pp::vec<double> &c : cols){c *= a;}; return *this;};
matrix& matrix::operator*=(matrix& B){
    dimension_check(*this, B);
    for(int i = 0; i < cols_size(); ++i){cols[i] *= B[i];}; 
    return *this;
};
matrix& matrix::operator/=(const double a){for(pp::vec<double> &c : cols){c /= a;}; return *this;};
matrix& matrix::operator/=(matrix& B){
    dimension_check(*this, B);
    for(int i = 0; i < cols_size(); ++i){cols[i] *= B[i];}; 
    return *this;
};
matrix& matrix::operator+=(const double a){for(pp::vec<double> &c : cols){c += a;}; return *this;};
matrix& matrix::operator+=(matrix& B){
    dimension_check(*this, B);
    for(int i = 0; i < cols_size(); ++i){cols[i] += B[i];}; 
    return *this;
};
matrix& matrix::operator-=(const double a){for(pp::vec<double> &c : cols){c -= a;}; return *this;};
matrix& matrix::operator-=(matrix& B){
    dimension_check(*this, B);
    for(int i = 0; i < cols_size(); ++i){cols[i] -= B[i];}; 
    return *this;
};

// #include"matrix.h"

// bool dimension_check(const matrix& A, const matrix& B){
//     if (A.ncols != B.ncols && A.nrows != B.nrows){throw std::runtime_error("Colomns and rows mismatch, cols = " + std::to_string(A.ncols) + ", " + std::to_string(B.ncols) + ", rows = " + std::to_string(A.nrows) + ", " + std::to_string(B.nrows) + ". \n");};
//     if (A.ncols != B.ncols){throw std::runtime_error("Colomns mismatch, cols = " + std::to_string(A.ncols) + ", " + std::to_string(B.ncols) + ". \n");};
//     if (A.nrows != B.nrows){throw std::runtime_error("Rows mismatch, rows = " + std::to_string(A.nrows) + ", " + std::to_string(B.nrows) + ". \n");};
//     return true;
// }

// matrix& matrix::operator*=(const double a){for(pp::vec<double> &c : cols){c *= a;}; return *this;};
// matrix& matrix::operator*=(matrix& B){
//     dimension_check(*this, B);
//     for(int i = 0; i < ncols; ++i){cols[i] *= B[i];}; 
//     return *this;
// };
// matrix& matrix::operator/=(const double a){for(pp::vec<double> &c : cols){c /= a;}; return *this;};
// matrix& matrix::operator/=(matrix& B){
//     dimension_check(*this, B);
//     for(int i = 0; i < ncols; ++i){cols[i] *= B[i];}; 
//     return *this;
// };
// matrix& matrix::operator+=(const double a){for(pp::vec<double> &c : cols){c += a;}; return *this;};
// matrix& matrix::operator+=(matrix& B){
//     dimension_check(*this, B);
//     for(int i = 0; i < ncols; ++i){cols[i] += B[i];}; 
//     return *this;
// };
// matrix& matrix::operator-=(const double a){for(pp::vec<double> &c : cols){c -= a;}; return *this;};
// matrix& matrix::operator-=(matrix& B){
//     dimension_check(*this, B);
//     for(int i = 0; i < ncols; ++i){cols[i] -= B[i];}; 
//     return *this;
// };