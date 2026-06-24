#include"matrix.h"
#include"tuple"
#include<random>
#include<functional>
#include<limits>
class PSO{
public:
    matrix pos, vel, p_opt_pos; // pos is current position, vel is current velocity and p_opt_pos are the current personal optimal positions
    pp::vec g_opt_pos, pb, a, b; // g_opt_pos is the current global optimal position and pb are the current personal optimal positions' values. a and b are the lower and upper bound for the initization/rattleing of the system
    double gb = std::numeric_limits<double>::infinity(), w = 0.99; // gb is the current global best position's value and w is the coefficient to maintain momentum.
    int dim, n_particles, amount_of_steps = 0; // amount of steps is used to check how many steps are needed for convergence.
    std::function<double(pp::vec&)> f;
    std::default_random_engine re;
    std::uniform_real_distribution<double> unif; // Used to generate random value for U1 and U2 in step method.
    PSO(std::function<double(pp::vec&)> F, pp::vec A, pp::vec B, int size = 10){ // This instantiates the system. a and b are the lower and upper boundaries for instantiation. Size is number of particles
        pp::vec p;        
        double value;
        f = F; a = A; b = B;
        dim = a.size(); n_particles = size;
        pos = matrix(dim, n_particles); vel = matrix(dim, n_particles);
        g_opt_pos = pp::vec(dim); pb = pp::vec(n_particles);
        std::uniform_real_distribution<double> unif_p; // Used to generate random numbers for the positions
        std::uniform_real_distribution<double> unif_v; // Used to generate random numbers for the velocities
        for (int i = 0; i < dim; ++i){
            unif_p.param(std::uniform_real_distribution<double>::param_type(a[i], b[i])); // Setting limits of random initial positions
            unif_v.param(std::uniform_real_distribution<double>::param_type((a[i] - b[i])/2, (b[i] - a[i])/2)); // Setting limits of random initial velocities
            for (int j = 0; j < n_particles; ++j){
                pos[j, i] = unif_p(re); vel[j, i] = unif_v(re); // Setting initial parameters
            }
        }
        p_opt_pos = pos; // Initial optimal positions are identical to initial positions
        for (int i = 0; i < n_particles; ++i){
            p = p_opt_pos.get_row(i); // Gets position of particle i
            value = f(p);
            pb[i] = value;
            if (value < gb){gb = value; g_opt_pos = p;} // Checks what the (initial) global best position and value is
        }
    }
    
    void step(); // This updates positions. 
    void optimize(int N = 5000, int patience = 100, bool Rattle = false, double gamma = 0.1, double Rattle_threshold = 4e-4); // This optimizes the system, i.e. perfroms steps until the system has converged (global best not improved in a certain amount of steps called patience) or a total number of steps have been performed (N). bool Rattle decides if one wishes to use the Rattle method in the optimization. gamma is for rattle. Rattle_threshold is used to check when to rattle the system.
    void rattle(double gamma = 0.1); // Randomizes velocities in case the system gets stuck. Velocities are randomized like in the instanization except gamma is multiplied on the random velocities if the user wants to dampen the rattleing.
    void show_results(); // Prints the global best position and its value
};
