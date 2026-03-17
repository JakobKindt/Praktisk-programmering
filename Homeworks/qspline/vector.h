#pragma once
#include <string>
#include<vector>
#include <stdexcept>
#include <initializer_list>
#include <iostream>
#include <cmath>
#include <algorithm>

namespace pp{
bool approx(double a, double b, double acc = 1e-9, double eps = 1e-9);

class vec {
private:
    std::vector<double> data;
public:
    vec(int n) : data(n) {};                                   // default
    vec() = default;                                           // default
    vec(const vec&) = default;                                 // copy
    vec(vec&&) = default;                                      // move
    ~vec() = default;                                          // destructor
    vec(std::initializer_list<double> init) : data(init){}

    int size() const {return data.size();}

    const double& operator[](int i) const {return data[i];} // add that it should check the size to confirm that it is possible.
    double& operator[](int i) {return data[i];} // add that it should check the size to confirm that it is possible.

    // assignment
    vec& operator=(const vec&) = default;                     // copy assignment
    vec& operator=(vec&&) = default;                          // move assignment

    // arithmetic
    vec& operator+=(const vec& w); // Addition of a vector
    vec& operator-=(const vec& w); // Subtraction of a vector

    vec& operator*=(const vec& w); // Multiplication of a vector
    vec& operator/=(const vec& w); // Division of a vector
    
    vec& operator*=(const double a); // Multiplication of a scalar
    vec& operator/=(const double a); // Division of a scalar
    vec& operator +=(const double a); // Addition of a scalar
    vec& operator -=(const double a); // substraction of a scalar

    
    // utility
    double norm() const;

    vec& project(const vec& w, bool demand_same_size = true);

    void print(const std::string& s = ""){ // for debugging // Prints coordinates
        if (size() <= 100){
        std::cout << s << "{";
        for (int i = 0; i + 1 < size();++i){
        std::cout << data[i] << ", ";
        }
        std::cout << data[int(size() - 1)] << "} \n";
        }
    }     

    // stream output
    friend std::ostream& operator<<(std::ostream& os, const vec& v); // Prints coordinates for <<
};

vec operator-(const vec& v); // Change of sign of a vector
vec operator-(const vec& v, const vec& w); // Subtraction between vectors
vec operator-(const vec& v, const double a); // Subtraction of constant 
vec operator-(const double a, const vec& v); // Subtraction of a vector to a constant
vec operator+(const vec& v, const vec& w); // Addition of vectors
vec operator+(const vec& v, const double a); // Addition of a constant
vec operator+(const double a, const vec& v); // Addition of a constant
vec operator*(const vec& v, const double a); // Multiplication of a constant
vec operator*(const double a, const vec& v); // Multiplication of a constant
vec operator*(const vec& v, const vec& w); // Multiplication of a vectors
vec operator/(const vec& v, const double a); // Division of a constant
vec operator/(const vec& v, const vec& w); // Division of a vectors

double dot(const vec& v, const vec& w); // Dot product between vectors

double norm(const vec& v);
vec project(const vec& v, const vec &w, bool demand_same_size = true); // Projects vector onto another vector

bool approx(const vec& v, const vec& w, double acc = 1e-6, double eps = 1e-6);
vec arange(const double xmin, const double xmax, const double dx);
vec linspace(const double xmin, const double xmax, const int size);
}