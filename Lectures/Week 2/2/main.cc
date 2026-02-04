#include<iostream>
#include<cstdio>
#include<vector>
int main(){
    double a = 1.0;
    double b = a;
    std::vector<double> v {1, 2, 3};
    auto u = v; // Here u creates a copy, i.e. a value type which was decided by the guy who made std::vector
    auto& w = v; // & is a reference which means that w points to the exact same place as v so that it is a reference type.
    std::cout << u << w << b; 
return 0;
}