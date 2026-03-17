#include"matrix.h"
#include<cassert>

double linterp(pp::vec& x, pp::vec& y, double z);
int binsearch(const pp::vec& x, double z);
double linterpInteg(pp::vec& x, pp::vec& y, double z);


class QS{
public:
    matrix Q;
    QS(pp::vec& x, pp::vec& y){
        Q = matrix(2, x.size() - 1); // Maybe size can be lowered by 1
        pp::vec bs(x.size() - 1), cs(x.size() - 1), ps(x.size() - 1);
        cs[0] = 0;
        assert(x[1] - x[0] > 0);
        ps[0] = (y[1] - y[0])/(x[1] - x[0]);
        bs[0] = ps[0];
        for (int i = 1; i < bs.size(); ++i){
            double dx = x[i + 1] - x[i];
            double dx_before = x[i] - x[i - 1];
            assert(dx > 0);
            double dy = y[i + 1] - y[i];
            ps[i] = dy/dx;
            cs[i] = (ps[i] - ps[i - 1] - cs[i - 1]*dx)/dx_before;
            bs[i] = ps[i] - cs[i]*dx;
        }
        Q.set_col(0, bs);
        Q.set_col(1, cs);
    }
    double qinterp(pp::vec& x, pp::vec& y, double z);
    double qinterpInteg(pp::vec& x, pp::vec& y, double z);
};