#include"vec.h"
#include<iostream>
void vec::print(const std::string& s) const {
        std::cout << s << x << " " << y << " " << z << std::endl;}

vec operator-(const vec& v){return vec(-v.x, -v.y, -v.z);} // Change of sign of a vector
vec operator-(const vec& v, const vec& w){return vec(v.x - w.x, v.y - w.y, v.z - w.z);} // Subtraction between vectors
vec operator-(const vec& v, const double a){return vec(v.x - a, v.y - a, v.z - a);} // Subtraction of constant 
vec operator-(const double a, const vec& v){return vec(-v.x + a, -v.y + a, -v.z + a);} // Subtraction of a vector to a constant

vec operator+(const vec& v, const vec& w) {return vec(v.x + w.x, v.y + w.y, v.z + w.z);} // Addition of vectors
vec operator+(const vec& v, const double a){return vec(v.x + a, v.y + a, v.z + a);} // Addition of a constant
vec operator+(const double a, const vec& v){return vec(v.x + a, v.y + a, v.z + a);} // Addition of a constant

vec operator*(const vec& v, const double a){return vec(v.x*a, v.y*a, v.z*a);} // Multiplication of a constant
vec operator*(const double a, const vec& v){return v*a;} // Multiplication of a constant
vec operator/(const vec& v, const double a){return vec(v.x/a, v.y/a, v.z/a);} // Division of a constant"

vec& vec::operator+=(const vec& w){x += w.x; y+= w.y, z += w.z; return *this;} // Addition of a vector
vec& vec::operator+=(const double a){x += a; y += a; z += a; return *this;} // Addition of a scalar
vec& vec::operator-=(const vec &w){x -= w.x, y-= w.y, z -= w.z; return *this;} // Subtraction of a vector
vec& vec::operator-=(const double a){x -= a; y -= a; z -= a; return *this;}
vec& vec::operator*=(const double a){x *= a; y *= a; z *= a; return *this;} // Multiplication of a scalar
vec& vec::operator/=(const double a){x /= a; y /= a; z/= a; return *this;} // Devision of a scalar

std::ostream& operator<<(std::ostream& os, const vec& v){os << "{" << v.x << ", " << v.y << ", " << v.z << "} "; return os;}
// bool approx(const vec& a, const vec& b){
// 	if(!approx(a.x,b.x))return false;
// 	if(!approx(a.y,b.y))return false;
// 	if(!approx(a.z,b.z))return false;
// 	return true;
// 	}