#include"matrix.h"
#include<functional>
#include"QR-factorization.h"
namespace OLS{

class lsfit{
public:
    pp::vec c;
    matrix Sigma;

    lsfit(std::vector<std::function<double(double)>>& fs, pp::vec& x, pp::vec& y, pp::vec& dy){
        matrix C(fs.size(), y.size());
        pp::vec b = y/dy;
        for (int i = 0; i < C.ncols; ++i){
            for (int j = 0; j < C.nrows; ++j){
                C[i, j] = fs[j](x[i])/dy[i];
            }
        }
        QR A(C);
        c = A.solve(b);
        matrix R_inv = A.R_inverse();
        Sigma = R_inv*R_inv.T();
    }
};

}