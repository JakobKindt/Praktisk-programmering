#include"hello.h"
#include<iostream>
void hello(){
    std::cout << "Hello from hello" << "\n";
    double x = 666;
    { // This is called a scope and is its own namespace. 
        double x = 1; // Shadowing. This replaces the outer x
        std::cout << x << "\n";
    }
    std::cout << x << "\n";
}