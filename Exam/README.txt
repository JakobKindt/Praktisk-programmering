I got project 8 about particle swarm optimization (PSO) which I implemented in a class called PSO. To instantiate it, one simply provides a function, two vectors (from my own vector class) which contain the lower and upper bounds for where we instantiate the particles and an integer of how many particles we want. The algorithm then instantiates the particles by randomizing their initial positions and velocities which are kept in matrices along side with the optimal positions, i.e. the positions at which the function so far is minimal, for the individual particles and for the particles as a group. It works in any amount of dimensions.

The class then has four methods, namely step, optimize, rattle and show_results which do the following:

void step(); // Takes a single step for the particles, i.e. updates positions, velocities and optimal positions and values.

void optimize(int N, int patience, bool Rattle, double gamma, double Rattle_threshold); // This optimizes the system, i.e. perfroms steps until the system has converged (global best not improved in a certain amount of steps called patience) or a total number of steps have been performed (N). bool Rattle decides if one wishes to use the Rattle method in the optimization. gamma is for rattle. Rattle_threshold is used to check when to rattle the system.

void rattle(double gamma = 0.1); Randomizes velocities in case the system gets stuck. Velocities are randomized like in the instanization except gamma is multiplied on the random velocities if the user wants to dampen the rattleing.

void show_results(); // Prints the global best position and its value


DO NOTE that rattle is not a standard method for the algorithm and is my own invention because I thought it could help the algorithm by minimizing the risks of ending in a local minima instead of a global one. However, after playing a bit with it, I think it is more useful to simply increase the amount of particles since "rattle" decreases performence and the cost-benefit of more particles seems to be better. So when optimizing, one can simply toggle it on and off and it is off by default.

---------------------------------------------------------------------------------------------
My algorithm works by writing:

std::function<double(pp::vec&)> f = [](pp::vec& x){...};
    pp::vec a{-1, -3, -30}, b{30, 13, 2};
    PSO A(f, a, b, 30);
    A.optimize(1e5, 500, false, 1e-2, 1e-2);
    A.show_results();