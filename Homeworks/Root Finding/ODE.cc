#include"ODE.h"
#include<cmath>
std::tuple<pp::vec,pp::vec> rkstep12(
	std::function<pp::vec(double,pp::vec)> f /* the f from dy/dx=f(x,y) */
	, double x                    /* the current value of the variable */
	, pp::vec y                    /* the current value y(x) of the sought function */
	, double h                     /* the step to be taken */
	)
{
	pp::vec k0 = f(x, y);              /* embedded lower order formula (Euler) */
	pp::vec k1 = f(x + h/2, y + k0*(h/2)); /* higher order formula (midpoint) */
	pp::vec yh = y + k1*h;              /* y(x+h) estimate */
	pp::vec dy = (k1 - k0)*h;           /* error estimate */
	return std::make_tuple(yh, dy);
}


std::tuple<std::vector<double>, std::vector<pp::vec>> driver(
	std::function<pp::vec(double, pp::vec)> F,/* the f from dy/dx=f(x,y) */
	double a, double b,           /* initial-point,final-point */
	pp::vec yinit,                /* y(initial-point) */
	double h,              /* initial step-size */
	double acc,             /* absolute accuracy goal */
	double eps              /* relative accuracy goal */
){
    double x=a; pp::vec y(yinit);
    std::vector<double> xlist; xlist.push_back(x);
    std::vector<pp::vec> ylist; ylist.push_back(y);
    do{
        if(x>=b) return std::make_tuple(xlist,ylist); /* job done */
        if(x+h>b) h=b-x;               /* last step should end at b */
        auto [yh, dy] = rkstep12(F,x,y,h);
        double tol = (acc+eps*yh.norm()) * std::sqrt(h/(b-a));
        double err = dy.norm();
        if(err<=tol){ // accept step
            x+=h; y=yh;
            xlist.push_back(x);
            ylist.push_back(y);
            }
        if(err>0) h *= std::min( std::pow(tol/err,0.25)*0.95 , 2.); // readjust stepsize
        else h*=2;
        }while(true);
}//driver