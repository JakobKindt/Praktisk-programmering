#include"Splines.h"
#include<iostream>
#include<cassert>
#include<cmath>

double linterp(pp::vec& x, pp::vec& y, double z){
	int i = binsearch(x, z);
  	double dx = x[i+1] - x[i];
  	assert(dx > 0);
  	double dy = y[i + 1] - y[i];
  	return y[i] + dy/dx*(z - x[i]);
}


int binsearch(const pp::vec& x, double z){/* locates the interval for z by bisection */ 
	assert( z >= x[0] && z <= x[x.size() - 1] );
	int i = 0, j = x.size() - 1;
	while(j - i > 1){
		int mid = (i + j)/2;
		if(z > x[mid]) i = mid; else j = mid;
		}
	return i;
}

double linterpInteg(pp::vec& x, pp::vec& y, double z){
    int s = binsearch(x, z);
    double sum = 0;
    for (int i = 0; i < s; ++i){
        double dx = x[i+1] - x[i];
        assert(dx > 0);
        sum += (y[i + 1] + y[i])*dx/2;
    }
    double dz = z - x[s];
    double dx = z - x[s];
    sum += y[s]*dx + (y[s + 1] - y[s])/(2*dx)*dz*dz;
    return sum;
}



double QS::qinterp(pp::vec& x, pp::vec& y, double z){
	int i = binsearch(x, z);
    double b = Q[0, i], c = Q[1, i];
  	return y[i] + b*(z - x[i]) + c*(z - x[i])*(z - x[i]);
}

double QS::qinterpInteg(pp::vec& x, pp::vec& y, double z){
    int s = binsearch(x, z);
    double sum = 0;
    for (int i = 0; i < s; ++i){
        double dx = dxs[i], b = Q[0, i], c = Q[1, i];
        sum += y[i]*dx + b*dx*dx/2 + c*dx*dx*dx/3;
    }
    double dx = z - x[s], b = Q[0, s], c = Q[1, s];
    sum += y[s]*dx + b*dx*dx/2 + c*dx*dx*dx/3;
    return sum;
}


double CS::cinterp(pp::vec& x, pp::vec& y, double z){
	int i = binsearch(x, z);
    double b = C[0, i], c = C[1, i], d = C[2, i];
  	return y[i] + b*(z - x[i]) + c*std::pow((z - x[i]), 2) + d*std::pow((z - x[i]), 3);
}

double CS::cinterpInteg(pp::vec& x, pp::vec& y, double z){
    int s = binsearch(x, z);
    double sum = 0;
    for (int i = 0; i < s; ++i){
        double dx = dxs[i], b = C[0, i], c = C[1, i], d = C[2, i];
        sum += y[i]*dx + b*dx*dx/2 + c*dx*dx*dx/3 + d*dx*dx*dx*dx/4;
    }
    double dx = z - x[s], b = C[0, s], c = C[1, s], d = C[2, s];
    sum += y[s]*dx + b*dx*dx/2 + c*dx*dx*dx/3 + d*dx*dx*dx*dx/4;;
    return sum;
}