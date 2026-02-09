#pragma once
#include <iostream>
#include <string>

struct vec {
    double x, y, z;

    // constructors
    vec(double x, double y, double z) : x(x), y(y), z(z) {}  // parameterized
    vec() : vec(0, 0, 0) {}                                    // default
    vec(const vec&) = default;                                 // copy - copy ctor: vec a(b)
    vec(vec&&) = default;                                      // move - move ctor: vec a(b + c)
    ~vec() = default;                                          // destructor

    // assignment
    vec& operator=(const vec&) = default;                     // copy assignment - copy assign : vec a = b, two seperate objects, vec&a = b, same object. Good practice is to have valuetype because one can always add & to make a reference type.
    vec& operator=(vec&&) = default;                          // move assignment

    // arithmetic
    vec& operator+=(const vec&);                              // vec& is a reference vec would make a new object. & is a reference.
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
vec operator+(const vec&, const vec&); // a = b + c, here b and c are passed as references, hence the &, because we do not need a new a whole new object, so we can simply reference them.
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
