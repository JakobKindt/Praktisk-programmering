#include"EVD.h"
#include<cmath>


void EVD::timesJ(matrix& A, int p, int q, double theta){
	double c = std::cos(theta), s = std::sin(theta);
	for(int i=0;i<A.nrows;i++){
		double aip=A[i,p], aiq=A[i,q];
		A[i, p] = c*aip - s*aiq;
		A[i, q] = s*aip + c*aiq;
		}
}

void EVD::Jtimes(matrix& A, int p, int q, double theta){
	double c = std::cos(theta), s = std::sin(theta);
	for(int j=0;j<A.nrows;j++){
		double apj = A[p,j], aqj = A[q,j];
		A[p, j] = c*apj + s*aqj;
		A[q, j] = -s*apj + c*aqj;
		}
}

