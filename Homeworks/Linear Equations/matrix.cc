#include"matrix.h"
bool dimension_check(const matrix& A, const matrix& B){
    if (A.ncols != B.ncols && A.nrows != B.nrows){throw std::runtime_error("Colomns and rows mismatch, cols = " + std::to_string(A.ncols) + ", " + std::to_string(B.ncols) + ", rows = " + std::to_string(A.nrows) + ", " + std::to_string(B.nrows) + ". \n");};
    if (A.ncols != B.ncols){throw std::runtime_error("Colomns mismatch, cols = " + std::to_string(A.ncols) + ", " + std::to_string(B.ncols) + ". \n");};
    if (A.nrows != B.nrows){throw std::runtime_error("Rows mismatch, rows = " + std::to_string(A.nrows) + ", " + std::to_string(B.nrows) + ". \n");};
    return true;
}

bool approx(const matrix& A, const matrix& B, double acc, double eps){
    dimension_check(A, B);
    for(int i = 0; i < A.ncols; ++i){for (int j = 0; j < A.nrows; ++j){if(!pp::approx(A[i, j], B[i, j], acc, eps)) return false;}}; 
    return true;
}


matrix matrix::T(){ // transposed
    matrix transposed(ncols, nrows);
    for (int i = 0; i < ncols; ++i){
        for (int j = 0; j < nrows; ++j){
            transposed[j, i] = cols[i*nrows + j];
        }
    }
    return transposed;
}

matrix T(const matrix& A){ // transposed
    matrix transposed(A.ncols, A.nrows);
    for (int i = 0; i < A.ncols; ++i){
        for (int j = 0; j < A.nrows; ++j){
            transposed[j, i] = A.cols[i*A.nrows + j];
        }
    }
    return transposed;
}

matrix matrix::reshape(int n, int m){
    if (n*m != nrows*ncols){throw std::runtime_error("Dimensions mismatchcols, cols = " + std::to_string(n) + ", " + std::to_string(ncols) + ", rows = " + std::to_string(m) + ", " + std::to_string(nrows) + ". \n");};
    matrix res(n, m);
    for (int i = 0; i < m;++i){for (int j = 0; j < n;++j)res[i, j] = cols[i*nrows + j];}
    nrows = n;
    ncols = m;
    return res;
}

matrix reshape(const matrix& A, const int& n, const int& m){
    if (n*m != A.nrows*A.ncols){throw std::runtime_error("Dimensions mismatchcols, cols = " + std::to_string(n) + ", " + std::to_string(A.ncols) + ", rows = " + std::to_string(m) + ", " + std::to_string(A.nrows) + ". \n");};
    matrix res(n, m);
    for (int i = 0; i < m;++i){for (int j = 0; j < n;++j)res[i, j] = A[i, j];}
    return res;
}

matrix& matrix::operator*=(const double a){cols *= a; return *this;};

matrix& matrix::operator/=(const double a){cols /= a; return *this;};
matrix& matrix::operator/=(matrix& B){
    dimension_check(*this, B);
    for(int i = 0; i < ncols; ++i){
        for (int j = 0; j < nrows; ++j){cols[i*nrows + j] /= B[i, j];}
        }; 
    return *this;
};



matrix& matrix::operator+=(const double a){cols += a; return *this;};
matrix& matrix::operator+=(matrix& B){
    dimension_check(*this, B);
    for(int i = 0; i < ncols; ++i){
        for (int j = 0; j < nrows; ++j){cols[i*nrows + j] += B[i, j];}
        }; 
    return *this;
};
matrix& matrix::operator-=(const double a){cols -= a; return *this;};
matrix& matrix::operator-=(matrix& B){
    dimension_check(*this, B);
    for(int i = 0; i < ncols; ++i){
        for (int j = 0; j < nrows; ++j){cols[i*nrows + j] -= B[i, j];}
        }; 
    return *this;
};


matrix operator*(const matrix& A, const matrix& B){
    if (A.nrows != B.ncols || A.ncols != B.nrows){throw std::runtime_error("Dimensions mismatch, cols = " + std::to_string(A.ncols) + ", " + std::to_string(B.ncols) + ", rows = " + std::to_string(A.nrows) + ", " + std::to_string(B.nrows) + ". \n");}
    matrix res(B.nrows, A.ncols);
    for(int i = 0; i < A.ncols; ++i){
        
        for (int j = 0; j < B.nrows; ++j){
            float sum = 0;
            for (int s = 0; s < A.nrows;++s){
                sum += A[i, s] * B[s, j];
                }
            res[i, j] = sum;
            }
        }; 
    return res;
};


pp::vec<double> operator*(const matrix& A, const pp::vec<double>& v){
    if (A.nrows != v.size()){throw std::runtime_error("Dimensions mismatch, rows = " + std::to_string(A.nrows) + ", " + std::to_string(v.size()) + ". \n");}
    pp::vec<double> res(A.ncols);
    for(int i = 0; i < A.ncols; ++i){
        float sum = 0;
        for (int j = 0; j < A.nrows;++j){
            sum += A[i, j] * v[j];
            }
        res[i] = sum;
        }; 
    return res;
};


pp::vec<double> operator*(const pp::vec<double>& v, const matrix& A){
    if (A.ncols != v.size()){throw std::runtime_error("Dimensions mismatch, cols = " + std::to_string(A.ncols) + ", " + std::to_string(v.size()) + ". \n");}
    pp::vec<double> res(A.nrows);
    for(int i = 0; i < A.nrows; ++i){
        float sum = 0;
        for (int j = 0; j < A.nrows;++j){
            sum += A[j, i] * v[j];
            }
        res[i] = sum;
        }; 
    return res;
};



matrix operator-(const matrix& A, const matrix& B){
    dimension_check(A, B);
    matrix res(A.nrows, A.ncols);
    for(int i = 0; i < A.ncols; ++i){
        for (int j = 0; j < A.nrows; ++j){res[i, j] = A[i, j] - B[i, j];}
        }; 
    return res;
};

matrix operator-(const matrix& A){
    matrix res(A.nrows, A.ncols);
    for(int i = 0; i < A.ncols; ++i){
        for (int j = 0; j < A.nrows; ++j){res[i, j] = -A[i, j];}
        }; 
    return res;
};


matrix operator-(const double a, const matrix& A){
    matrix res(A.nrows, A.ncols);
    for(int i = 0; i < A.ncols; ++i){
        for (int j = 0; j < A.nrows; ++j){res[i, j] = a - A[i, j];}
        }; 
    return res;
};


matrix operator-(const matrix& A, const double a){
    matrix res(A.nrows, A.ncols);
    for(int i = 0; i < A.ncols; ++i){
        for (int j = 0; j < A.nrows; ++j){res[i, j] = A[i, j] - a;}
        }; 
    return res;
};

matrix operator+(const matrix& A, const matrix& B){
    dimension_check(A, B);
    matrix res(A.nrows, A.ncols);
    for(int i = 0; i < A.ncols; ++i){
        for (int j = 0; j < A.nrows; ++j){res[i, j] = A[i, j] + B[i, j];}
        }; 
    return res;
};

matrix operator+(const matrix& A, const double a){
    matrix res(A.nrows, A.ncols);
    for(int i = 0; i < A.ncols; ++i){
        for (int j = 0; j < A.nrows; ++j){res[i, j] = A[i, j] + a;}
        }; 
    return res;
};

matrix operator+(const double a, const matrix& A){
    matrix res(A.nrows, A.ncols);
    for(int i = 0; i < A.ncols; ++i){
        for (int j = 0; j < A.nrows; ++j){res[i, j] = a + A[i, j];}
        }; 
    return res;
};

matrix operator*(const matrix& A, const double a){
    matrix res(A.nrows, A.ncols);
    for(int i = 0; i < A.ncols; ++i){
        for (int j = 0; j < A.nrows; ++j){res[i, j] = A[i, j] * a;}
        }; 
    return res;
};

matrix operator*(const double a, const matrix& A){
    matrix res(A.nrows, A.ncols);
    for(int i = 0; i < A.ncols; ++i){
        for (int j = 0; j < A.nrows; ++j){res[i, j] = a * A[i, j];}
        }; 
    return res;
};

matrix operator/(const matrix& A, const double a){
    matrix res(A.nrows, A.ncols);
    for(int i = 0; i < A.ncols; ++i){
        for (int j = 0; j < A.nrows; ++j){res[i, j] = A[i, j] / a;}
        }; 
    return res;
};

matrix operator/(const double a, const matrix& A){
    matrix res(A.nrows, A.ncols);
    for(int i = 0; i < A.ncols; ++i){
        for (int j = 0; j < A.nrows; ++j){res[i, j] = a / A[i, j];}
        }; 
    return res;
};



pp::vec<double> matrix::get_row(int i){
    pp::vec<double> res(nrows);
    for (int j = 0; j < nrows; ++j){
        res[j] = cols[i*nrows + j];
    }
    return res;
}
matrix& matrix::set_row(int i, pp::vec<double>& v){
    if (v.size() != nrows){throw std::runtime_error("Dimensions mismatch, rows = " + std::to_string(nrows) + ", " + std::to_string(v.size()) + ". \n");}
    for (int j = 0; j < nrows; ++j){
        cols[i*nrows + j] = v[j];
    }
    return *this;
}

matrix& matrix::set_row(int i, double a){
    for (int j = 0; j < nrows; ++j){
        cols[i*nrows + j] = a;
    }
    return *this;
}

pp::vec<double> matrix::get_col(int i){
    pp::vec<double> res(ncols);
    for (int j = 0; j < ncols; ++j){
        res[j] = cols[i + j*nrows];
    }
    return res;
}
matrix& matrix::set_col(int i, pp::vec<double>& v){
    if (v.size() != ncols){throw std::runtime_error("Dimensions mismatch, cols = " + std::to_string(ncols) + ", " + std::to_string(v.size()) + ". \n");}
    for (int j = 0; j < ncols; ++j){
        cols[i + j*nrows] = v[j];
    }
    return *this;
}

matrix& matrix::set_col(int i, double a){
    for (int j = 0; j < ncols; ++j){
        cols[i + j*nrows] = a;
    }
    return *this;
}

matrix identity (const int& i){
    matrix res(i, i);
    for (int j = 0; j < i;++j){
        res[j, j] = 1;
    }
    return res;
}