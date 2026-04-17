#include"Root.h"
#include"QR-factorization.h"

pp::vec newton(std::function<pp::vec(pp::vec)>& f, pp::vec& start, double acc){
	pp::vec x = start;
	pp::vec fx = f(x), z, fz;
	do{ /* Newton's iterations */
		if(fx.norm() < acc) break; /* job done */
		matrix J = jacobian(f, x);
		if (acc < 0){}
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





// pp::vec newton(std::function<pp::vec(pp::vec)>& f, pp::vec& start, double acc){
// 	pp::vec x = start;
// 	pp::vec fx = f(x), z, fz;
// 	do{ /* Newton's iterations */
// 		if(fx.norm() < acc) break; /* job done */
// 		matrix J = jacobian(f, x);
// 		QR QRJ(J);
// 		fx = -fx;
// 		pp::vec Dx = QRJ.solve(fx); /* Newton's step */
// 		fx = -fx;
// 		double lamb = 1;
// 		do{ /* linesearch */
// 			z = x + lamb*Dx;
// 			fz = f(z);
// 			if(fz.norm() < (1 - lamb/2)*fx.norm() ) break;
// 			if(lamb < std::pow(2, -26) ) break; // lambda min has been set to std::pow(2, -26). Maybe it should be altered
// 			lamb /= 2;
// 			}while(true);
// 		x = z; fx = fz;
// 		}while(true);
// 	return x;
// }

// pp::vec newton(std::function<pp::vec(pp::vec)>& f, pp::vec& start, double acc){
// 	pp::vec x = start;
// 	pp::vec fx = f(x), z, fz;
// 	fx.print("fx = ");
// 	// do{ /* Newton's iterations */
// 	// 	if(fx.norm() < acc) break; /* job done */
// 	// 	matrix J = jacobian(f, x);
		
// 	// 	QR QRJ(J);
// 	// 	J.print("J = ");
// 	// 	// fx = -fx;
// 	// 	// pp::vec Dx = QRJ.solve(fx); /* Newton's step */
// 	// 	// fx = -fx;
// 	// 	// double lamb = 1;
// 	// 	// do{ /* linesearch */
// 	// 	// 	z = x + lamb*Dx;
// 	// 	// 	fz = f(z);
// 	// 	// 	if(fz.norm() < (1 - lamb/2)*fx.norm() ) break;
// 	// 	// 	if(lamb < std::pow(2, -26) ) break; // lambda min has been set to std::pow(2, -26). Maybe it should be altered
// 	// 	// 	lamb /= 2;
// 	// 	// 	}while(true);
// 	// 	// x = z; fx = fz;
// 	// 	}while(true);
// 	// do{ /* Newton's iterations */
// 		// if(fx.norm() < acc) break; /* job done */
// 		matrix J = jacobian(f, x);
// 		std::cout << "acc = " << acc << "\n";
// 		QR QRJ(J);
// 		J.print("J = ");
// 		std::cout << "acc = " << J[0, 0] << "\n";
// 		std::cout << "acc = " << J[0, 1] << "\n";
// 		std::cout << "acc = " << J.nrows << "acc = " << J.cols << "\n";
// 		// fx = -fx;
// 		// pp::vec Dx = QRJ.solve(fx); /* Newton's step */
// 		// fx = -fx;
// 		// double lamb = 1;
// 		// do{ /* linesearch */
// 		// 	z = x + lamb*Dx;
// 		// 	fz = f(z);
// 		// 	if(fz.norm() < (1 - lamb/2)*fx.norm() ) break;
// 		// 	if(lamb < std::pow(2, -26) ) break; // lambda min has been set to std::pow(2, -26). Maybe it should be altered
// 		// 	lamb /= 2;
// 		// 	}while(true);
// 		// x = z; fx = fz;
// 		// }while(true);
// 	return x;
// }



// matrix jacobian(std::function<pp::vec(pp::vec)>& f, pp::vec& x, pp::vec& fx, pp::vec& dx){
// 	int dim = x.size(), dim2 = fx.size();
    
// 	matrix J(dim, dim2);
//     pp::vec df(dim2);
// 	// x += dx;
// 	// df = f(x) - fx;
// 	for(int i = 0; i < dim; i++){
// 		x[i] += dx[i];
// 		df = f(x) - fx;
// 		for(int j = 0; j < dim2; j++){J[i, j] = df[j]/dx[i];}
// 		x[i] -= dx[i];
// 		}
// 	// x -= dx;
// 	return J;
// }

// matrix jacobian(std::function<pp::vec(pp::vec)>& f, pp::vec& x){
// 	int dim = x.size(), s = 0;
// 	double max = x[s];
// 	for (int i = 0; i < dim; ++i){if (x[i] > max){s = i; max = x[i];}}
// 	pp::vec dx(dim);
// 	dx += max*std::pow(2, -26);
// 	pp::vec fx = f(x);
// 	return jacobian(f, x, fx, dx);
// }


