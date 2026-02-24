#include"matrix.h"
class QR{
public:
    matrix Q,R;
    // QR(matrix& A){ /* the above "decomp" is the constructor here */
    //     Q = A;
    //     R = matrix(A.nrows, A.nrows);
    //   /* orthogonalize Q and fill-in R */
    //     pp::vec<double> u(A.nrows);
    //     pp::vec<double> a(A.ncols);
    //     for (int i = 0; i < A.nrows; ++i){ // coloumn
    //         u = A.get_col(i);
    //         a = A.get_col(i);
    //         for (int j = 0; j < i; ++j){ // row
    //             u -= project(a, Q.get_col(j));
    //             R[j, i] = dot(Q.get_col(j), a);
    //         }
    //         u /= u.norm();
    //         Q.set_col(i, u);
    //         R[i, i] = dot(Q.get_col(i), a);
    //     }
    //   }

    QR(matrix& A){ /* the above "decomp" is the constructor here */
        Q = A;
        R = matrix(A.nrows, A.nrows);
        
      /* orthogonalize Q and fill-in R */
        pp::vec<double> u(A.ncols);
        pp::vec<double> a(A.ncols);
        pp::vec<double> nul(u.size());
        for (int i = 0; i < A.nrows; ++i){ // coloumn
            u = A.get_col(i);
            a = A.get_col(i);
            for (int j = 0; j < i; ++j){ // row
                u -= project(a, Q.get_col(j));
                R[j, i] = dot(Q.get_col(j), a);
            }
            // std::cout << u << "\n";
            
            if (approx(u, nul)){u = nul;}
            else{u /= u.norm();}
            
            Q.set_col(i, u);
            R[i, i] = dot(Q.get_col(i), a);
        }
      }
    // QR(matrix& A){ /* the above "decomp" is the constructor here */
    //     Q = A;
    //     R = matrix(A.ncols, A.ncols);
    //   /* orthogonalize Q and fill-in R */
    //     pp::vec<double> u(A.nrows);
    //     pp::vec<double> a(A.ncols);
    //     for (int i = 0; i < A.nrows; ++i){ // coloumn
    //         u = A.get_col(i);
    //         a = A.get_col(i);
    //         for (int j = 0; j < i; ++j){ // row
    //             u -= Q.get_col(j);
    //             R[j, i] = dot(Q.get_col(j), a);
    //         }
            
    //         R[i, i] = u.norm();
    //         u /= u.norm();
    //         Q.set_col(i, u);
            
    //     }
    //   }
   pp::vec<double> solve(pp::vec<double>&);
   double det();
   matrix inverse();
};