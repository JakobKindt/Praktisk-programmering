#include"matrix.h"
#include<cassert>

double linterp(pp::vec& x, pp::vec& y, double z);
int binsearch(const pp::vec& x, double z);
double linterpInteg(pp::vec& x, pp::vec& y, double z);


class QS{
public:
    matrix Q;
    pp::vec dxs, dys;
    QS(pp::vec& x, pp::vec& y){
        int n = x.size() - 1;
        dxs = pp::vec(n);
        dys = pp::vec(n);
        Q = matrix(n, 2);
        pp::vec bs(n), cs(n), ps(n);
        for (int i = 0; i < n; ++i){assert(x[i + 1] - x[i] > 0); dxs[i] = x[i + 1] - x[i]; dys[i] = y[i + 1] - y[i]; ps[i] = dys[i]/dxs[i];}
        for (int i = 1; i < n; ++i){
            cs[i] = (ps[i] - ps[i - 1] - cs[i - 1]*dxs[i - 1])/dxs[i];
        }
        for (int i = n - 2; i >= 0; --i){
            cs[i] = (ps[i + 1] - ps[i] - cs[i + 1]*dxs[i + 1])/(2*dxs[i]);
        }
        for (int i = 0; i < n; ++i){bs[i] = ps[i] - cs[i]*dxs[i];}
        Q.set_row(0, bs);
        Q.set_row(1, cs);
    }
    double qinterp(pp::vec& x, pp::vec& y, double z);
    double qinterpInteg(pp::vec& x, pp::vec& y, double z);
};


class CS{
public:
    matrix C;
    pp::vec dxs, dys;
    CS(pp::vec& x, pp::vec& y){
        int n = x.size() - 1;
        C = matrix(n, 3); // Maybe size can be lowered by 1
        dxs = pp::vec(n);
        dys = pp::vec(n);
        pp::vec bs(n), cs(n), ds(n), ps(n), B(n), D(n), B_raw(n), D_raw(n), Q(n - 1), as(n);
        for (int i = 0; i < n; ++i){assert(x[i + 1] - x[i] > 0); dxs[i] = x[i + 1] - x[i]; dys[i] = y[i + 1] - y[i]; ps[i] = dys[i]/dxs[i];}
        B_raw[0] = 3*ps[0];
        Q[0] = 1;
        D_raw[0] = 2;
        B[0] = B_raw[0];
        D[0] = D_raw[0];

        for (int i = 1; i < n - 1; ++i){
            double ratio = dxs[i - 1]/dxs[i];
            Q[i] = ratio;
            B_raw[i] = 3*(ps[i - 1] + ps[i]*ratio);
            D_raw[i] = 2*ratio + 2;
            D[i] = D_raw[i] - Q[i - 1]/D[i - 1];
            B[i] = B_raw[i] - B[i - 1]/D[i - 1];
        }
        B_raw[n - 1] = 3*ps[n - 2];
        D_raw[n - 1] = 2;
        D[n - 1] = D_raw[n - 1] - Q[n - 2]/D[n - 2];
        B[n - 1] =  B_raw[n - 1] - B[n - 2]/D[n - 2];
        bs[n - 1] = B[n - 1]/D[n - 1];
        for (int i = n - 2; i >= 0; --i){
            double dx = dxs[i];
            bs[i] = (B[i] - Q[i]*bs[i + 1])/D[i];
            cs[i] = (3*ps[i] - 2*bs[i] - bs[i + 1])/dx;
            ds[i] = (bs[i] + bs[i + 1] - 2*ps[i])/(dx*dx);
            as[i] = ps[i] - cs[i]*dx - ds[i]*dx*dx;
        }
        C.set_row(0, as);
        C.set_row(1, cs);
        C.set_row(2, ds);
    }
    double cinterp(pp::vec& x, pp::vec& y, double z);
    double cinterpInteg(pp::vec& x, pp::vec& y, double z);
};