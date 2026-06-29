#include"PSO.h"
#include<cmath> // Used for exp
#include<chrono> // Used for timing
#include<thread>
#include<fstream>


void time_PSO(double& time, double& steps, double& min, std::function<double(pp::vec&)>f, pp::vec& a, pp::vec& b, int N){
    auto start = std::chrono::high_resolution_clock::now();
    PSO A(f, a, b, N);
    A.optimize(1e5, 500, false, 1e-1, 25);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::milliseconds>(stop - start);
    time = duration.count();
    steps = A.amount_of_steps;
    min = A.gb; // This is simply here for debugging by checking that the actual global minima is found.
}

int main(){
    std::cout << "First, I check if my algorithm works as intended for the function f(x_1, x_2, x_3) = \\sum_{i = 1}^3 |x_i| which has an obivious minima at 0.\n\n"; 

    std::function<double(pp::vec&)> f = [](pp::vec& x){ // Simple function with obvious minima at origo with no local minima to check algorithm works as intended for simple functions
        return std::abs(x[0]) + std::abs(x[1]) + std::abs(x[2]);
    };
    pp::vec a{-1, -3, -30}, b{30, 13, 2};
    auto start = std::chrono::high_resolution_clock::now(); // Timing
    PSO A(f, a, b, 50);
    A.optimize(1e5, 1000);
    A.show_results();
    auto stop = std::chrono::high_resolution_clock::now(); // Timing
    auto duration = duration_cast<std::chrono::milliseconds>(stop - start); // Timing
    std::cout << "The algorithm took "<< duration.count() << " milliseconds. \n\nI wish to compare this with what happens if I use my rattle algorithm for the same function. Do note that this rattle method is something which is not standard for the algorithm but I have decided to investigate it a bit.\n";

    start = std::chrono::high_resolution_clock::now();
    PSO B(f, a, b, 50);
    B.optimize(1e5, 1000, true, 1e-4, 5e-5); // Test if rattle also give usefull results
    B.show_results();
    
    stop = std::chrono::high_resolution_clock::now();
    duration = duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "The algorithm took "<< duration.count() << " milliseconds. \nIn this case, the rattle method produces the same results but were much slower, i.e. it is a very expensive addition to the algorithm in this case. This is most likely because it rattles so often, so one could have added a limit for rattling or decreased the 'decay' parameter in the rattle method in my PSO.cc.\n\n";


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
    D.optimize(1e5, 500, true, 1e-1, 25);
    D.show_results();
    stop = std::chrono::high_resolution_clock::now();
    duration = duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "The algorithm took "<< duration.count() << " milliseconds. \n\nIn this case the time for convergence is comparable and it also managed to find a global minima instead of a local one which is exactly what rattle was supposed to do which is a proof of concept for why rattle might be useful. However, if we use PSO more like intended and have a decent amount of particles, i.e. 25 instead of 5, we also get closer to the global minima and it does not increase the runtime by much as can be seen below.\n\n";

    start = std::chrono::high_resolution_clock::now();
    PSO E(f2, a, b, 25);
    E.optimize(1e5, 500);
    E.show_results();
    stop = std::chrono::high_resolution_clock::now();
    duration = duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "The algorithm took "<< duration.count() << " milliseconds. \n\nThis shows that if one needs to find the minima, it is more useful to simply increase the number of particles.\n\n";

    a *= 5; b*= 5; // The "Box", i.e. limits of where the particles may be, is increased to inflate convergence time to make the following investigation more prominent.
    std::cout << "As a final thing, I now investigate how the number of particles influences the time of convergence (See fig_times.svg) and how many steps are needed for convergence (see fig_convergence.svg) where I define convergence as when the global minima stops decreasing. The number of steps needed to converge is constant except for an unfortunate instantiation which makes sense since the more particles we have, the more likely it is that a particle by chance is initiated close to the global minima but at some point the grid is covered sufficiently well so more particles won't necessarily imply less steps to converge. I have also fitted f(x) = ax + b and g(x) = cx^d to the time of convergence. Both fits seem decent. It makes sense that it is somewhat linear but not perfectly linear, as each particle walks around seperately (of course not independently) meaning linearity but the different amount of particles also needed a different amount of steps to convergence (as was seen in the other figure), so not perfectly linear.\n\n";
    
    // Parallelization
    pp::vec Ns{40, 150, 200, 250, 500, 750, 1000, 1500, 2000};
    int nthreads = Ns.size();
    std::vector<std::thread> threads;
    threads.reserve(nthreads);
    pp::vec times(nthreads);
    pp::vec amounts_of_steps(nthreads);
    pp::vec minimas(nthreads);
    

    for (int i = 0; i < nthreads; ++i){
        threads.emplace_back(time_PSO, std::ref(times[i]), std::ref(amounts_of_steps[i]), std::ref(minimas[i]), std::cref(f2), std::ref(a), std::ref(b), Ns[i]); // Investigation of one N
    }
    for (std::thread& thread : threads) {thread.join();}


    std::string outfile = "data.txt";
    std::ofstream myoutput(outfile);
    for (int i = 0; i < nthreads; ++i){
        myoutput << Ns[i] << " " << times[i] << " " << amounts_of_steps[i] - 500 << " " << minimas[i] << "\n"; // Saving output
    }
    myoutput.close();
return 0;
}