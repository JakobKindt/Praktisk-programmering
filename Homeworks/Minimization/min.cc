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
        for (int i = 0; i < dim; ++i){H[i, j] = dg_phi[i]/dxj;} // Make sure that it is not H[j, i]
        x[j] -= dxj;
    }
    return H;
}

// double newton(std::function<double(pp::vec)>& phi, pp::vec x, double acc){
//     int count = 0, max_count = 1000;
//     while (true){ // Newton iterations
//         pp::vec g = gradient(phi, x);
//         if (g.norm() < acc){break;}   // job done
//         matrix H = hessian(phi, x);
//         g = -g;
//         QR QRH(H);
//         pp::vec dx = QRH.solve(g);
//         g = -g;
//         double lamb = 1;
//         while (lamb >= 1./1024){       // backtracking linesearch
//             if (phi(x + lamb*dx) < phi(x)){break;} // good step
//             lamb /= 2;
//         }
//         x += lamb*dx;
//         ++count; if(count == max_count){break;}
//     }
//     return phi(x);
// }