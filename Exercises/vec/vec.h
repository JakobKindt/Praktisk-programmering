#pragma once
#include <iostream>
#include <string>

struct vec {
    double x, y, z;

    // constructors
    vec(double x, double y, double z) : x(x), y(y), z(z) {}  // parameterized
    vec() : vec(0, 0, 0) {}                                    // default
    vec(const vec&) = default;                                 // copy
    vec(vec&&) = default;                                      // move
    ~vec() = default;                                          // destructor

    // assignment
    vec& operator=(const vec&) = default;                     // copy assignment
    vec& operator=(vec&&) = default;                          // move assignment

    // arithmetic
    vec& operator+=(const vec&);
    vec& operator-=(const vec&);
    vec& operator*=(double);
    vec& operator/=(double);
    vec& operator+=(const double);
    vec& operator-=(const double);

    // utility
    void set(double a, double b, double c) { x = a; y = b; z = c; }
    void print(const std::string& s = "") const;              // for debugging
    double norm(void);
    vec& project(const vec&);

    // stream output
    friend std::ostream& operator<<(std::ostream&, const vec&);
};

// non-member operators
vec operator-(const vec&);
vec operator-(const vec&, const vec&);
vec operator-(const vec&, const double);
vec operator-(const double, const vec&);
vec operator+(const vec&, const vec&);
vec operator+(const vec&, const double);
vec operator+(const double, const vec&);
vec operator*(const vec&, double);
vec operator*(double, const vec&);
vec operator/(const vec&, double);
double dot(const vec&, const vec&);
double norm(const vec&);
vec project(const vec&, const vec&);

// approximate equality
bool approx(const vec&, const vec&, double acc = 1e-6, double eps = 1e-6);
