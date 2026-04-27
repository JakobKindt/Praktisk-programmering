#pragma once
#include"matrix.h"
class QR{
public:
    matrix Q,R;
    QR(matrix& A){ /* the above "decomp" is the constructor here */
        Q = A;
        R = matrix(A.nrows, A.nrows);
        
      /* orthogonalize Q and fill-in R */
        pp::vec u(A.ncols);
        pp::vec a(A.ncols);
        pp::vec nul(u.size());
        for (int i = 0; i < A.nrows; ++i){ // coloumn
            u = A.get_col(i);
            a = A.get_col(i);
            for (int j = 0; j < i; ++j){ // row
                u -= project(a, Q.get_col(j));
                R[j, i] = dot(Q.get_col(j), a);
            }
            
            if (approx(u, nul)){u = nul;}
            else{u /= u.norm();}
            
            Q.set_col(i, u);
            R[i, i] = dot(Q.get_col(i), a);
        }
      }
   pp::vec solve(pp::vec);
   double det();
   matrix inverse();
   matrix R_inverse();
};