#include"PSO.h"
#include<cmath>

void PSO::step(){ // This method takes a single step
    double U1, U2, value;
    pp::vec po, v, p;
    pos += vel; // updates positions
    for (int i = 0; i < n_particles; ++i){ // Updates velocities
        v = vel.get_row(i);
        p = pos.get_row(i);
        U1 = unif(re); U2 = unif(re);
        po = p_opt_pos.get_row(i);
        v = w*v + U1*(po - p) + U2*(g_opt_pos - p);
        for (int j = 0; j < dim; ++j){
            if (pos[i, j] < a[j]){pos[i, j] = a[j]; v[j] *= -0.25;} // Stops and bounces off of boundaries
            if (pos[i, j] > b[j]){pos[i, j] = b[j]; v[j] *= -0.25;} // Stops and bounces off of boundaries
        }
        vel.set_row(i, v);
        value = f(p); // value is dummy double for value of function defined in PSO.h
        if (value < pb[i]){pb[i] = value; p_opt_pos.set_row(i, p);} // Checks and potentially updates personal best.
    }
    for (int i = 0; i < n_particles; ++i){ // Checks and potentially updates global best
        value = pb[i];
        if (value < gb){gb = value; g_opt_pos = p_opt_pos.get_row(i);}
    }
};


void PSO::optimize(int N, int patience, bool Rattle, double gamma, double Rattle_threshold){ // This optimizes the system, i.e. perfroms steps until the system has converged (global best not improved in a certain amount of steps called patience) or a total number of steps have been performed (N). gamma is for rattle. Rattle_threshold is used to check when to rattle the system.
    int timer = 0, Rattle_counter = 0;
    double temp_gb = gb, max_speed, norm_squared, decay = 1;
    for (int i = 0; i < N; ++i){
        ++timer;
        if (timer == patience + 1){std::cout << "System has converged prematurely after " << amount_of_steps - patience << " steps.\n"; break;}
        ++amount_of_steps;
        step();
        if (gb < temp_gb){temp_gb = gb; timer = 0;} // std::cout << "a step has been performed\n";} // Checks if system has improved, if so, it resets the timer.
        
        
        if (Rattle){ // This is not needed in the optimization algorithm but I thought it was a nice addition of the algorithm to decrease the probablity of stopping prematurely. It rattles the system if the particles becomes (approximately, defined by Rattle_threshold) stationary, i.e. gives each particle a title kick to its velocity.
            max_speed = -std::numeric_limits<double>::infinity(); // Sets the measured maximum speed of the particles to -infinity as no speeds have been measured 
            for (int j = 0; j < n_particles; ++j){ // Measures the speed of the fastest moving particle
                norm_squared = vel.get_row(j).norm_squared(); // Measures the speed of particle i
                if (norm_squared > max_speed){max_speed = norm_squared;} // Compares speed and potentially updates max speed
            }
            if (max_speed < Rattle_threshold*decay){ // If the max speed is below the threshold, it rattles the system. The threshold gets lowered the more we rattle since that presumably means that we are closer and closer to the minina, so we wish to rattle less often
                // timer = std::min({timer, Rattle_counter + 1}); // The timer decreases if the system rattles but decreases less and less to avoid the code from running to long. This makes it such that one can rattle at most "patience" times.
                rattle(gamma*decay); // The rattle amount decreases when we rattle more and more since it presumably means that we are closer and closer to the minima, so we wish to rattle less and less.
                ++Rattle_counter;
                decay *= 0.98;
            }
        }
    }

    if (Rattle){
        std::cout << "The system was rattled " << Rattle_counter << " times. \n"; 
    }
}


void PSO::rattle(double gamma){ // This gives each particle a random velocity kick, i.e. rattles the system.
    std::uniform_real_distribution<double> unif_v; // Used to generate random numbers for the velocities
    for (int i = 0; i < dim; ++i){
        unif_v.param(std::uniform_real_distribution<double>::param_type((a[i] - b[i])/2, (b[i] - a[i])/2)); // Setting limits of random kick velocities
        for (int j = 0; j < n_particles; ++j){
            vel[j, i] += unif_v(re)*gamma; // Velocity kick.
        }
    }
}


void PSO::show_results(){ // Prints the global best position and its value
    std::cout << "Global optimal position = " << g_opt_pos << "\nGlobal optimal value = " << gb << "\n";
}