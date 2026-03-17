#include"Splines.h"
#include<iostream>
#include"cassert"

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
    // sum += y[s]*dx + y[s]*dx/2;
    sum += y[s]*dx + (y[s + 1] - y[s])/(2*dx)*dz*dz;
    // sum += y[s]*dx + (y[s + 1] + y[s])/(2*dx)*(z - x[s])*(z - x[s]);
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
        double dx = x[i+1] - x[i], b = Q[0, i], c = Q[1, i];
        assert(dx > 0);
        sum += y[i]*dx + b*dx*dx/2 + c*dx*dx*dx/3;
    }
    double dx = z - x[s], b = Q[0, s], c = Q[1, s];
    sum += y[s]*dx + b*dx*dx/2 + c*dx*dx*dx/3;
    return sum;
}