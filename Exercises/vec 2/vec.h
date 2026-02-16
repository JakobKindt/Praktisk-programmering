#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <complex>
template<typename T>
bool approx(T a, T b, double acc = 1e-9, double eps = 1e-9) {
        T diff = std::abs(a - b);
        if (diff <= acc) return true;  // absolute tolerance
        T max_ab = std::max(std::abs(a), std::abs(b));
        return diff <= eps * max_ab;   // relative tolerance
    }
template<typename> struct is_complex : std::false_type{};
template<typename T> struct is_complex<std::complex<T>> : std::true_type {};

template<typename T>
struct vec {
    T x{}, y{}, z{};

    // constructors
    vec(T x, T y, T z) : x(x), y(y), z(z) {}  // parameterized
    vec() = default;                                           // default
    vec(const vec&) = default;                                 // copy
    vec(vec&&) = default;                                      // move
    ~vec() = default;                                          // destructor

    // assignment
    vec& operator=(const vec&) = default;                     // copy assignment
    vec& operator=(vec&&) = default;                          // move assignment

    // arithmetic
    vec& operator+=(const vec& w){x += w.x; y += w.y; z += w.z; return *this;}; // Addition of a vector
    vec& operator-=(const vec& w){x -= w.x; y -= w.y; z -= w.z; return *this;}; // Subtraction of a vector
    vec& operator*=(T a) {x *= a; y *= a; z *= a; return *this;}; // Multiplication of a scalar
    vec& operator/=(T a) {x /= a; y /= a; z /= a; return *this;}; // Division of a scalar
    vec& operator+=(const T a) {x += a; y += a, z += a; return *this;}; // Addition of a scalar
    vec& operator-=(const T a) {x -= a; y -= a; z -= a; return *this;}; // substraction of a scalar


    // utility
    void set(T a, T b, T c) { x = a; y = b; z = c;}
    void print(const std::string& s = "") {std::cout << s << x << " " << y << " " << z << "\n";};              // for debugging // Prints coordinates
    T norm(void){return std::sqrt(std::pow(std::abs(x), 2) + std::pow(std::abs(y), 2) + std::pow(std::abs(z), 2));};
    
    vec<T>& project(const vec<T>& w) {*this = (x*w.x + y*w.y + z*w.z)/dot(w, w)*w; return *this;} // Projects onto another vector;

    // stream output
    friend std::ostream& operator<<(std::ostream& os, const vec& v) {os << "{" << v.x << ", " << v.y << ", " << v.z << "} "; return os;}; // Prints coordinates for <<

    
    friend vec operator-(const vec& v) {return vec(-v.x, -v.y, -v.z);} // Change of sign of a vector
    friend vec operator-(const vec& v, const vec& w) {return vec(v.x - w.x, v.y - w.y, v.z - w.z);} // Subtraction between vectors
    friend vec operator-(const vec& v, const T a) {return vec(v.x - a, v.y - a, v.z - a);} // Subtraction of constant 
    friend vec operator-(const T a, const vec& v) {return vec(-v.x + a, -v.y + a, -v.z + a);} // Subtraction of a vector to a constant

    friend vec operator+(const vec& v, const vec& w) {return vec(v.x + w.x, v.y + w.y, v.z + w.z);} // Addition of vectors
    friend vec operator+(const vec& v, const T a) {return vec(v.x + a, v.y + a, v.z + a);} // Addition of a constant
    friend vec operator+(const T a, const vec& v) {return vec(v.x + a, v.y + a, v.z + a);} // Addition of a constant

    friend vec operator*(const vec& v, const T a) {return vec(v.x*a, v.y*a, v.z*a);} // Multiplication of a constant
    friend vec operator*(const T a, const vec& v) {return vec(v.x*a, v.y*a, v.z*a);} // Multiplication of a constant
    friend vec operator/(const vec& v, const T a) {return vec(v.x/a, v.y/a, v.z/a);} // Division of a constant"

    // friend T dot(const vec<T>& v, const vec<T>& w) {return v.x*w.x + v.y*w.y + v.z*w.z;} // Dot product between vectors
    friend T dot(const vec<T>& v, const vec<T>& w) {
        if constexpr (is_complex<T>::value){
        return v.x*std::conj(w.x) + v.y*std::conj(w.y) + v.z*std::conj(w.z);} // Dot product between vectors
        else{
            return v.x*w.x + v.y*w.y + v.z*w.z;
        }
    }
    friend T norm(const vec<T>& v){return std::sqrt(std::pow(std::abs(v.x), 2) + std::pow(std::abs(v.y), 2) + std::pow(std::abs(v.z), 2));} // Caluclates the norm of a vector
    friend vec<T> project(const vec<T>& v, const vec<T>& w) {return dot(v, w)/dot(w, w)*w;} // Projects vector onto another vector

    friend bool approx(const vec<T>& v, const vec<T>& w, double acc = 1e-6, double eps = 1e-6){
	if(!approx(v.x, w.x, acc, eps)) return false;
	if(!approx(v.y, w.y, acc, eps)) return false;
	if(!approx(v.z, w.z, acc, eps)) return false;
	return true;
    }   
};