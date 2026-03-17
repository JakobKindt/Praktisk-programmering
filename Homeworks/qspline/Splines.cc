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
    for (int i = 0; i < s - 1; ++i){
        double dx = x[i+1] - x[i];
        assert(dx > 0);
        sum += (y[i + 1] + y[i])*dx/2;
    }
    double dx = z - x[s];
    sum += y[s]*dx + (y[s + 1] + y[s])/(2*dx)*(z - x[s])*(z - x[s]);
    return sum;
}



double qinterp(pp::vec& x, pp::vec& y, double z){
	int i = binsearch(x, z);
  	double dx = x[i + 1] - x[i];
  	assert(dx > 0);
  	double dy = y[i + 1] - y[i];
    // double pi = dy/dx
    double c_i1 = 


  	return y[i] + dy/dx*(z - x[i]);
}

double polinterp ( int n , double x , double y , double z ) {
    double s =0, p;
    double c_i1 = 
    for (int i =0; i<n ; i++) {
        p=1; 
        for (int k=0;k<n ; k++) if (k!= i) p*=(z - x[k])/(x[i]-x[k]);
        s+=y [i] * p ; }
    return s;}

double qinterpInteg(pp::vec& x, pp::vec& y, double z){
    int s = binsearch(x, z);
    double sum = 0;
    for (int i = 0; i < s - 1; ++i){
        double dx = x[i+1] - x[i];
        assert(dx > 0);
        sum += (y[i + 1] + y[i])*dx/2;
    }
    double dx = z - x[s];
    sum += y[s]*dx + (y[s + 1] + y[s])/(2*dx)*(z - x[s])*(z - x[s]);
    return sum;
}