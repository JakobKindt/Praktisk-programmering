// #include<iostream>
#include"PSO.h"
#include<cmath> // Used for exp
#include<chrono> // Used for timing
#include<thread>
#include<fstream>


void time_PSO(double& time, std::function<double(pp::vec&)>f, pp::vec& a, pp::vec& b, int N){
    auto start = std::chrono::high_resolution_clock::now();
    PSO A(f, a, b, N);
    A.optimize(1e5, 500);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::milliseconds>(stop - start);
    time = duration.count();
}

int main(){
    std::cout << "First, I check if my algorithm works as intended for the function f(x_1, x_2, x_3) = \\sum_{i = 1}^3 |x_i| which has an obivious minima at 0.\n\n"; 

    std::function<double(pp::vec&)> f = [](pp::vec& x){ // Simple function with obvious minima at origo with no local minima to check algorithm works as intended for simple functions
        return std::abs(x[0]) + std::abs(x[1]) + std::abs(x[2]);
    };
    pp::vec a{-1, -3, -30}, b{30, 13, 2};
    auto start = std::chrono::high_resolution_clock::now();
    PSO A(f, a, b, 30);
    A.optimize(1e5, 500);
    A.show_results();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "The algorithm took "<< duration.count() << " milliseconds. \n\nI wish to compare this with what happens if I use my rattle algorithm for the same function.\n";

    start = std::chrono::high_resolution_clock::now();
    PSO B(f, a, b, 30);
    B.optimize(1e5, 500, true, 1e-5, 2e-2); // Test if rattle also give usefull results
    B.show_results();
    
    stop = std::chrono::high_resolution_clock::now();
    duration = duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "The algorithm took "<< duration.count() << " milliseconds. \nIn this case, the rattle method makes it such that the precision is much greater. However, it also took approximate 5 times longer and it did not stop because it stop converging but rather because the max optimization steps was reached, so this is an expensive addition to the algorithm. \n\n";

    std::cout << "Now I test the algorithm on a more complicated function which is the sum of 4 gaussian functions in 4D (where I have no analytical expression for the minima, but given the weights and standard deviations of the gaussian functions, see main directly, the minima should be close to the center of the third gaussian function by design). Here I use 5 particles. \n\n";

    a = pp::vec{-2, -2, -2, -2}; b = pp::vec{2, 2, 2, 2};
    matrix mus{{-1, 0.6, -0.3, -0.5}, {0.8, 0.9, -1.4, -0.1}, {0.2, 1.2, 0.4, -0.3}, {-0.7, 0.8, 0.6, -1.1}};
    pp::vec As{-6, 3, -12, -8}, sigmas{0.3, 0.8, 0.4, 1.};
    std::function<double(pp::vec&)> f2 = [&As, &mus, &sigmas](pp::vec& x){ // Complicated function which is just the sum of some gaussian functions
        double value = 0, norm;
        pp::vec mu;
        for (int i = 0; i < As.size(); ++i){
            norm = (x - mus.get_row(i)).norm();
            value += As[i]*std::exp(-norm*norm/(2*sigmas[i]*sigmas[i]));
        }
        return value;
    };
    
    start = std::chrono::high_resolution_clock::now();
    PSO C(f2, a, b, 5);
    C.optimize(1e5, 500);
    C.show_results();
    stop = std::chrono::high_resolution_clock::now();
    duration = duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "The algorithm took "<< duration.count() << " milliseconds. \n\nNow with rattle. \n";


    start = std::chrono::high_resolution_clock::now();
    PSO D(f2, a, b, 5);
    D.optimize(1e5, 500, true);
    D.show_results();
    stop = std::chrono::high_resolution_clock::now();
    duration = duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "The algorithm took "<< duration.count() << " milliseconds. \n\nIn this case, rattle made it 20-25 times slower, but it found the actual global minima instead of a local one which is a proof of concept for why rattle might be usefull. However, if we use PSO more like intended and have a decent amount of particles, i.e. 50 instead of 5, we also find the global minima and it is much still much faster than with rattle.\n\n";

    start = std::chrono::high_resolution_clock::now();
    PSO E(f2, a, b, 50);
    E.optimize(1e5, 500);
    E.show_results();
    stop = std::chrono::high_resolution_clock::now();
    duration = duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "The algorithm took "<< duration.count() << " milliseconds. \n\n This shows that if one needs to find the minima, it is more useful to simply increase the number of particles.\n"; // Rattle might still be useful if one needs an obscure amount of precision since the simple function case showed that we were much closer to 0 with rattle than without it\n";


    pp::vec Ns{5, 50, 250, 500, 750, 1000, 1500, 2000};
    int nthreads = Ns.size();
    std::vector<std::thread> threads;
    threads.reserve(nthreads);
    pp::vec times(nthreads);
    

    for (int i = 0; i < nthreads; ++i){
        threads.emplace_back(time_PSO, std::ref(times[i]), std::cref(f2), std::ref(a), std::ref(b), Ns[i]);
    }
    for (std::thread& thread : threads) {thread.join();}
    std::cout << times << "\n";


    std::string outfile = "times.txt";
    std::ofstream myoutput(outfile);
    for (int i = 0; i < nthreads; ++i){
        myoutput << Ns[i] << " " << times[i] << "\n";
    }
    myoutput.close();
return 0;
}

// int main(){
//     std::cout << "First, I check if my algorithm works as intended for the function f(x_1, x_2, x_3) = \\sum_{i = 1}^3 |x_i| which has an obivious minima at 0.\n\n"; 

//     std::function<double(pp::vec&)> f = [](pp::vec& x){ // Simple function with obvious minima at origo with no local minima to check algorithm works as intended for simple functions
//         return std::abs(x[0]) + std::abs(x[1]) + std::abs(x[2]);
//     };
//     pp::vec a{-1, -3, -30}, b{30, 13, 2};
//     auto start = std::chrono::high_resolution_clock::now();
//     PSO A(f, a, b, 30);
//     A.optimize(1e5, 500);
//     A.show_results();
//     auto stop = std::chrono::high_resolution_clock::now();
//     auto duration = duration_cast<std::chrono::milliseconds>(stop - start);
//     std::cout << "The algorithm took "<< duration.count() << " milliseconds. \n\nI wish to compare this with what happens if I use my rattle algorithm for the same function.\n";

//     start = std::chrono::high_resolution_clock::now();
//     PSO B(f, a, b, 30);
//     B.optimize(1e5, 500, true, 1e-5, 2e-2); // Test if rattle also give usefull results
//     B.show_results();
    
//     stop = std::chrono::high_resolution_clock::now();
//     duration = duration_cast<std::chrono::milliseconds>(stop - start);
//     std::cout << "The algorithm took "<< duration.count() << " milliseconds. \nIn this case, the rattle method makes it such that the precision is much greater. However, it also took approximate 5 times longer and it did not stop because it stop converging but rather because the max optimization steps was reached, so this is an expensive addition to the algorithm. \n\n";

//     std::cout << "Now I test the algorithm on a more complicated function which is the sum of 4 gaussian functions in 4D (where I have no analytical expression for the minima, but given the weights and standard deviations of the gaussian functions, see main directly, the minima should be close to the center of the third gaussian function by design). Here I use 5 particles. \n\n";

//     a = pp::vec{-2, -2, -2, -2}; b = pp::vec{2, 2, 2, 2};
//     matrix mus{{-1, 0.6, -0.3, -0.5}, {0.8, 0.9, -1.4, -0.1}, {0.2, 1.2, 0.4, -0.3}, {-0.7, 0.8, 0.6, -1.1}};
//     pp::vec As{-6, 3, -12, -8}, sigmas{0.3, 0.8, 0.4, 1.};
//     std::function<double(pp::vec&)> f2 = [&As, &mus, &sigmas](pp::vec& x){ // Complicated function which is just the sum of some gaussian functions
//         double value = 0, norm;
//         pp::vec mu;
//         for (int i = 0; i < As.size(); ++i){
//             norm = (x - mus.get_row(i)).norm();
//             value += As[i]*std::exp(-norm*norm/(2*sigmas[i]*sigmas[i]));
//         }
//         return value;
//     };
    
//     start = std::chrono::high_resolution_clock::now();
//     PSO C(f2, a, b, 5);
//     C.optimize(1e5, 500);
//     C.show_results();
//     stop = std::chrono::high_resolution_clock::now();
//     duration = duration_cast<std::chrono::milliseconds>(stop - start);
//     std::cout << "The algorithm took "<< duration.count() << " milliseconds. \n\nNow with rattle. \n";


//     start = std::chrono::high_resolution_clock::now();
//     PSO D(f2, a, b, 5);
//     D.optimize(1e5, 500, true);
//     D.show_results();
//     stop = std::chrono::high_resolution_clock::now();
//     duration = duration_cast<std::chrono::milliseconds>(stop - start);
//     std::cout << "The algorithm took "<< duration.count() << " milliseconds. \n\nIn this case, rattle made it 20-25 times slower, but it found the actual global minima instead of a local one which is a proof of concept for why rattle might be usefull. However, if we use PSO more like intended and have a decent amount of particles, i.e. 50 instead of 5, we also find the global minima and it is much still much faster than with rattle.\n\n";

//     start = std::chrono::high_resolution_clock::now();
//     PSO E(f2, a, b, 500);
//     E.optimize(1e5, 50);
//     E.show_results();
//     stop = std::chrono::high_resolution_clock::now();
//     duration = duration_cast<std::chrono::milliseconds>(stop - start);
//     std::cout << "The algorithm took "<< duration.count() << " milliseconds. \n\n This shows that if one needs to find the minima, it is more useful to simply increase the number of particles.\n"; // Rattle might still be useful if one needs an obscure amount of precision since the simple function case showed that we were much closer to 0 with rattle than without it\n";

// return 0;
// }


// int main(){
//     // PART A:
//     std::cout << "Part A and B \n";
//     std::function<double(double)> f = [] (double x){return std::cos(5*x - 1)*std::exp(-x*x);}; // Test function
//     int N = 60;
//     pp::vec xs_train = pp::linspace(-1, 1 + 2./N, N), xs_plot = pp::linspace(-3., 3., N);
//     pp::vec ys_train(xs_train.size()), ys_plot(xs_plot.size());
//     for (int i = 0; i < xs_train.size(); ++i){ys_train[i] = f(xs_train[i]);}
//     ann B(4, 1e-1, 1e-1); // Neurons, initial learning rate and threshold for norm of gradient before stopping prematurely
//     B.train(xs_train, ys_train);
//     std::string outfile = "data.txt";
//     std::ofstream myoutput(outfile);
//     double x, y;
//     pp::vec res(4);
//     for (int i = 0; i < xs_plot.size(); i++){
//         x = xs_plot[i];
//         res = B.total_response(x); // f, F, df, ddf
//         myoutput << x << " " << res[0] << " " << res[1] << " " << res[2] << " " << res[3] << "\n";
//     }
//     myoutput << "\n\n";
//     for (int i = 0; i < xs_train.size(); i++){
//         x = xs_train[i];
//         y = ys_train[i];
//         myoutput << x << " " << y << "\n";
//     }
//     myoutput.close();
//     // ------------------------------------------------------------------------------------------------------------------------------------------------
//     std::cout << "\n\nPart C \n";

//     N = 120;
//     xs_plot = pp::linspace(-1, 1, N);
//     xs_train = pp::linspace(-1, 1 + 2./N, N);
//     std::function<double(pp::vec&)> Phi = [](pp::vec& z){ // z[0] = x, z[1] = y, z[2] = y', z[3] = y''
//         return z[3] - 3*z[2] + 2*z[1] + z[0]; // Theoretical solution c_1e^2x + c_2e^3x - x/6 - 5/36
//     };
//     annc C(4, 1e-2, 1e-2, 0, 1./2, 0); // Neurons, initial learning rate and threshold for norm of gradient before stopping prematurely // int n, double lr, double tol, double c, double yc, double dyc
//     C.train(xs_train, Phi);

//     std::string outfile2 = "data2.txt";
//     std::ofstream myoutput2(outfile2);
//     for (int i = 0; i < xs_plot.size(); i++){
//         x = xs_plot[i];
//         res = C.total_response(x); // f, F, df, ddf
//         myoutput2 << x << " " << res[0] << " " << res[1] << " " << res[2] << " " << res[3] << "\n";
//     }
//     myoutput2 << "\n\n";
//     xs_train = pp::linspace(-0.5, 0.5 + 2./N, N); // Smaller training set
//     annc D(4, 1e-2, 1e-2, 0, 1./2, 0); // Neurons, initial learning rate and threshold for norm of gradient before stopping prematurely // int n, double lr, double tol, double c, double yc, double dyc
//     D.train(xs_train, Phi);
//     for (int i = 0; i < xs_plot.size(); i++){
//         x = xs_plot[i];
//         res = D.total_response(x); // f, F, df, ddf
//         myoutput2 << x << " " << res[0] << " " << res[1] << " " << res[2] << " " << res[3] << "\n";
//     }
//     myoutput2.close();
//     std::cout << "After investigating a bit it turns out that the initial (random) guess for the optimizable parameters have a big influence. So does what interval we are looking at and the number of nodes, so this method is rather unstable when it comes to solving differential equations with only one (or two) initial conditions. \n";
// return 0;
// }
