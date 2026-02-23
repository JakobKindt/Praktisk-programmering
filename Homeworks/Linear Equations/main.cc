#include<iostream>
#include<cstdio>
// #include"vec.h"
#include"matrix.h"
int main(){
	// int n=5;
	pp::vec<double> v{1., 2., 3.};
    pp::vec<double> w{4., 5., 6.};
    v *= w;
    v.print();
	// for(int i=0;i<n;i++)v[i]=i+1;
	// for(int i=0;i<n;i++)u[i]=i+100;
	// v.print("v=");
	// u.print("u=");
	// v+=u;
	// v.print("new v=");
	// u*=1000;
	// u.print("even newer u=");
    matrix B{v, w};
    matrix C{v, w};
    B.print("B = ");
    B *= 2.5;
    B.print("new B = ");
    C.print("C = ");
    int n = B.ncols;
    int m = B.nrows;
    std::cout << n << ", " << m << "\n";
    bool test = dimension_check(B, C);
    std::cout << test << "\n";
    B *= C;
    B.print("B*C = ");
return 0;
}