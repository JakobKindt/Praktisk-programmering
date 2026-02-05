#include"vec.h"
#include<cmath> // For std::sqrt
#include<iostream>
void vec::print(const std::string& s) const {std::cout << s << x << " " << y << " " << z << std::endl;} // Prints coordinates

vec operator-(const vec& v){return vec(-v.x, -v.y, -v.z);} // Change of sign of a vector
vec operator-(const vec& v, const vec& w){return vec(v.x - w.x, v.y - w.y, v.z - w.z);} // Subtraction between vectors
vec operator-(const vec& v, const double a){return vec(v.x - a, v.y - a, v.z - a);} // Subtraction of constant 
vec operator-(const double a, const vec& v){return vec(-v.x + a, -v.y + a, -v.z + a);} // Subtraction of a vector to a constant

vec operator+(const vec& v, const vec& w) {return vec(v.x + w.x, v.y + w.y, v.z + w.z);} // Addition of vectors
vec operator+(const vec& v, const double a){return vec(v.x + a, v.y + a, v.z + a);} // Addition of a constant
vec operator+(const double a, const vec& v){return vec(v.x + a, v.y + a, v.z + a);} // Addition of a constant

vec operator*(const vec& v, const double a){return vec(v.x*a, v.y*a, v.z*a);} // Multiplication of a constant
vec operator*(const double a, const vec& v){return vec(v.x*a, v.y*a, v.z*a);} // Multiplication of a constant
vec operator/(const vec& v, const double a){return vec(v.x/a, v.y/a, v.z/a);} // Division of a constant"

vec& vec::operator+=(const vec& w){x += w.x; y+= w.y, z += w.z; return *this;} // Addition of a vector
vec& vec::operator+=(const double a){x += a; y += a; z += a; return *this;} // Addition of a scalar
vec& vec::operator-=(const vec &w){x -= w.x, y-= w.y, z -= w.z; return *this;} // Subtraction of a vector
vec& vec::operator-=(const double a){x -= a; y -= a; z -= a; return *this;}
vec& vec::operator*=(const double a){x *= a; y *= a; z *= a; return *this;} // Multiplication of a scalar
vec& vec::operator/=(const double a){x /= a; y /= a; z/= a; return *this;} // Devision of a scalar

std::ostream& operator<<(std::ostream& os, const vec& v){os << "{" << v.x << ", " << v.y << ", " << v.z << "} "; return os;} // Prints coordinates for <<

double vec::norm(){return std::sqrt(x*x + y*x + z*z);} // Caluclates the norm of a vector
vec& vec::project(const vec& w){*this = (x*w.x + y*w.y + z*w.z)/dot(w, w)*w; return *this;} // Projects onto another vector
double dot(const vec& v, const vec& w){return v.x*w.x + v.y*w.y + v.z*w.z;} // Dot product between vectors
double norm(const vec& v){return std::sqrt(v.x*v.x + v.y*v.y + v.z*v.z);} // Calculates norm of a vector
vec project(const vec& v, const vec& w){return dot(v, w)/dot(w, w)*w;} // Projects vector onto another vector

bool approx(double a, double b, double acc = 1e-9, double eps = 1e-9) {
    double diff = std::abs(a - b);
    if (diff <= acc) return true;  // absolute tolerance
    double max_ab = std::max(std::abs(a), std::abs(b));
    return diff <= eps * max_ab;   // relative tolerance
}

bool approx(const vec& v, const vec& w, double acc, double eps){
	if(!approx(v.x, w.x, acc, eps)) return false;
	if(!approx(v.y, w.y, acc, eps)) return false;
	if(!approx(v.z, w.z, acc, eps)) return false;
	return true;
}