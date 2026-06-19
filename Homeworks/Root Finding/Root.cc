#include"Root.h"
#include"QR-factorization.h"

pp::vec newton(std::function<pp::vec(pp::vec)>& f, pp::vec& start, double acc){
	pp::vec x = start;
	pp::vec fx = f(x), z, fz;
	do{ /* Newton's iterations */
		if(fx.norm() < acc) break; /* job done */
		matrix J = jacobian(f, x);
		QR QRJ(J);
		fx = -fx;
		pp::vec Dx = QRJ.solve(fx); /* Newton's step */
		fx = -fx;
		double lamb = 1;
		do{ /* linesearch */
			z = x + lamb*Dx;
			fz = f(z);
			if(fz.norm() < (1 - lamb/2)*fx.norm() ) break;
			if(lamb < std::pow(2, -26) ) break; // lambda min has been set to std::pow(2, -26). Maybe it should be altered
			lamb /= 2;
			}while(true);
		x = z; fx = fz;
		}while(true);
	return x;
}



matrix jacobian(std::function<pp::vec(pp::vec)>& f, pp::vec& x, pp::vec& fx, pp::vec& dx){
	int dim = x.size();
    
	matrix J(dim, dim);
    pp::vec df(dim);
	for(int i = 0; i < dim; i++){
		x[i] += dx[i];
		df = f(x) - fx;
		for(int j = 0; j < dim; j++){J[j, i] = df[j]/dx[i];}
		x[i] -= dx[i];
		}
	return J;
}


matrix jacobian(std::function<pp::vec(pp::vec)>& f, pp::vec& x){
	int dim = x.size(), s = 0;
	double max = x[s];
	for (int i = 0; i < dim; ++i){if (x[i] > max){s = i; max = x[i];}}
	pp::vec dx(dim);
	dx += std::max(max, 1.)*std::pow(2, -26);
	pp::vec fx = f(x);
	return jacobian(f, x, fx, dx);
}

pp::vec quasi_newton(std::function<pp::vec(pp::vec)>& f, pp::vec& start, double acc){
	pp::vec x = start;
	pp::vec fx = f(x), z, fz, Dx, dx, df;
	matrix J, B;
	J = jacobian(f, x);
	QR QRJ(J);
	B = QRJ.inverse(); // B is inverse of J
	do{ /* Newton's iterations */
		if(fx.norm() < acc) break; /* job done */
		
		Dx = -B*fx; // QRJ.solve(fx); /* Newton's step */
		double lamb = 1;
		do{ /* linesearch */
			z = x + lamb*Dx;
			fz = f(z);
			if(fz.norm() < (1 - lamb/2)*fx.norm() ) break;
			if(lamb < std::pow(2, -26) ) break; // lambda min has been set to std::pow(2, -26). Maybe it should be altered
			lamb /= 2;
			}while(true);
		dx = z - x; df = fz - fx;
		x = z; fx = fz;
		if(lamb < std::pow(2, -7) ){
			J = jacobian(f, x);
			QR QRJ(J);
			B = QRJ.inverse(); // B is inverse of J}; // lambda min has been set to 1/128 (2^-7). Maybe it should be altered
		}
		else{update_inverse_jacobian(df, dx, B);}
		}while(true);
	return x;
}


void update_inverse_jacobian(pp::vec& df, pp::vec& dx, matrix& B){
	int dim = df.size();
	matrix dB(dim, dim);
	pp::vec v, w;

	v = (dx - B*df)/(dx*B*df); w = dx * B; // Good Broyden's method, i.e. eq. 17
	// v = (dx - B*df)/(df*df); w = df; // Bad Broyden's method, i.e. eq. 18
	// v = (dx - B*df)/(dx*df); w = dx; // eq. 19
	for (int i = 0; i < dim; ++i){
		for (int j = 0; j < dim; ++j){
			dB[i, j] = v[j]*w[i];
		}
	}
	B += dB;
}