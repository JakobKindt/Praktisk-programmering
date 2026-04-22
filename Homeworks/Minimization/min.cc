#include"min.h"

std::tuple<double, pp::vec, int> newton(std::function<double(pp::vec)>& phi, pp::vec x, double acc, int max_count){
    int count = 0;
    while (true){ // Newton iterations
        pp::vec g = gradient(phi, x); // Gradient of phi is calculated here
        if (g.norm() < acc){break;}   // job done
        matrix H = hessian(phi, x); // Gradient of phi is calculated here. Perhaps one can just save the result from above and insert it here.
        g = -g;
        QR QRH(H);
        pp::vec dx = QRH.solve(g);
        g = -g;
        double lamb = 1;
        while (lamb >= 1./1024){       // backtracking linesearch
            if (phi(x + lamb*dx) < phi(x)){break;} // good step
            lamb /= 2;
        }
        x += lamb*dx;
        ++count; if(count == max_count){break;}
    }
    double phi_x = phi(x);
    return std::tie(phi_x, x, count); // Returns a tuple consisting of minima where it it found
}

pp::vec gradient(std::function<double(pp::vec)>& phi, pp::vec& x){
    double phi_x = phi(x);
    int dim = x.size();
    pp::vec g_phi(dim);
    for (int i = 0; i < dim; ++i){
        double dxi = (1 + std::abs(x[i]))*std::pow(2, -26);
        x[i] += dxi;
        g_phi[i] = (phi(x) - phi_x)/dxi;
        x[i] -= dxi;
    }
    return g_phi;
}

matrix hessian(std::function<double(pp::vec)>& phi, pp::vec& x){
    int dim = x.size();
    matrix H(dim, dim);
    pp::vec g_phi_x = gradient(phi, x); 
    for (int j = 0; j < dim; ++j){
        double dxj = (1 + std::abs(x[j])) * std::pow(2, -13);
        x[j] += dxj;
        pp::vec dg_phi = gradient(phi, x) - g_phi_x;
        for (int i = j; i < dim; ++i){H[i, j] = dg_phi[i]/dxj; if (i > j){H[j, i] = dg_phi[i]/dxj;}} // Hessian symmetric
        x[j] -= dxj;
    }
    return H;
}

std::tuple<double, pp::vec, int> newton_central(std::function<double(pp::vec)>& phi, pp::vec x, double acc, int max_count){
    int count = 0, dim = x.size();
    pp::vec g(dim), x0, x1, x2, x3;
    double phi_x, phi_x_f, phi_x_b, dxi, dxj;
    matrix H(dim, dim);
    while (true){ // Newton iterations
        phi_x = phi(x);
        
        
        for (int i = 0; i < dim; ++i){
            x0 = x, x1 = x, x2 = x, x3 = x; // Four different versions of x to minimize rounding errors from repeating addition and subtraction of dx.
            dxi = (1 + std::abs(x[i]))*std::pow(2, -13); // -26
            x0[i] += dxi; x1[i] += dxi;
            x2[i] -= dxi; x3[i] -= dxi;
            phi_x_f = phi(x0); phi_x_b = phi(x3); 
            g[i] = (phi_x_f - phi_x_b)/(2*dxi); // Gradient of phi is calculated here
            H[i, i] = (phi_x_f - 2*phi_x + phi_x_b)/(dxi*dxi); // Reusing function call - Not sure if this is what is intended.
            for (int j = i + 1; j < dim; ++j){
                dxj = (1 + std::abs(x[j]))*std::pow(2, -13);
                x0[j] += dxj; x1[j] -= dxj;
                x2[j] += dxj; x3[j] -= dxj;
                H[i, j] = (phi(x0) - phi(x1) - phi(x2) + phi(x3))/(4*dxi*dxj); H[j, i] = H[i, j];
                x0[j] -= dxj; x1[j] += dxj;
                x2[j] -= dxj; x3[j] += dxj;
            }
            x0[i] -= dxi; x1[i] -= dxi;
            x2[i] += dxi; x3[i] += dxi;
        }
        // pp::vec g = gradient(phi, x); 
        if (g.norm() < acc){break;}   // job done
        QR QRH(H);
        pp::vec dx = QRH.solve(-g);
        double lamb = 1;
        while (lamb >= 1./1024){       // backtracking linesearch
            if (phi(x + lamb*dx) < phi_x){break;} // good step
            lamb /= 2;
        }
        x += lamb*dx;
        ++count; if(count == max_count){break;}
    }
    phi_x = phi(x);
    return std::tie(phi_x, x, count); // Returns a tuple consisting of minima where it it found
}