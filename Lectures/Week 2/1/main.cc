#include<iostream> //angles means only look at system places, "" means look first in the current directionary (dictionary?).
#include<cstdio> // Checks if the input has the right type? i.e. is an int, float etc.
#include<math.h>
#include "hello.h" //.h means here, <> or {}? means that it has to search in the dictionary. 
#include"sfuns.h"
int main() {
    hello(); //hello is a function which is defined elsewhere
    double x = 1;
    double y = sfuns::fgamma(x); // sfuns:: gets things from the name space sfuns.
    std::cout << "fgamma(1) = " << y << "\n";
    for (double x = 1; x<= 9; x += 1){
        std::cout << "fgamma(" << x << ") = " << sfuns::fgamma(x) << " tgamma(" << x << ") = " << std::tgamma(x) << "\n"; // "\t tgamma(" << x << ") = " << std::tgamma(x) << "\n";
    }
    std::cout << "gamma(-1) = " << std::lgamma(-1.0) << "\n";
    // std::printf("fgamma(1) = %g\n", y); // if we were coding in C?
return 0;
}