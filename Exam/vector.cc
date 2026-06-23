#include"vector.h"


namespace pp {
// arithmetic
vec& vec::operator+=(const vec& w){
    int n = size();
    if (n != w.size()) {throw std::runtime_error("Dimensions of added vector mismatches");}
    for (int i = 0; i < n;++i){
        data[i] += w[i];
    }
    return *this;
} // Addition of a vector
vec& vec::operator-=(const vec& w){
    int n = size();
    if (n != w.size()) {throw std::runtime_error("Dimensions of subtracted vector mismatches");}
    for (int i = 0; i < n;++i){
        data[i] -= w[i];
    }
    return *this;
} // Subtraction of a vector

vec& vec::operator*=(const vec& w){
    int n = size();
    if (n != w.size()) {throw std::runtime_error("Dimensions of multiplied vector mismatches");}
    for (int i = 0; i < n;++i){
        data[i] *= w[i];
    }
    return *this;
} // Multiplication of a vector
vec& vec::operator/=(const vec& w){
    int n = size();
    if (n != w.size()) {throw std::runtime_error("Dimensions of divided vector mismatches");}
    for (int i = 0; i < n;++i){
        data[i] /= w[i];
    }
    return *this;
} // Division of a vector

vec& vec::operator*=(const double a){for (int i = 0; i < size();++i){data[i] *= a;}; return *this;} // Multiplication of a scalar
vec& vec::operator/=(const double a){for (int i = 0; i < size();++i){data[i] /= a;}; return *this;} // Division of a scalar
vec& vec::operator +=(const double a){for (int i = 0; i < size();++i){data[i] += a;}; return *this;} // Addition of a scalar
vec& vec::operator -=(const double a){for (int i = 0; i < size();++i){data[i] -= a;}; return *this;} // substraction of a scalar


// utility
double vec::norm() const{
    double sum = 0;
    for (int i = 0; i < size(); ++i){
        sum += data[i]*data[i];
    }
    return std::sqrt(sum);
}

vec vec::push_back(const double a){
    vec v(size() + 1);
    for (int i = 0; i < size(); ++i){v[i] = data[i];}
    v[size()] = a;
    *this = v;
    return *this;
}

vec& vec::project(const vec& w, bool demand_same_size){
    int n = size(), m = w.size();
    if (n != m && demand_same_size) {throw std::runtime_error("Dimensions mismatches");}
    int min = std::min(n, m);
    double sum = 0;
    for (int i = 0; i < min;++i){
        sum += data[i]*w[i];
    }
    *this = sum/dot(w, w)*w;
    return *this;
}
  

// stream output
std::ostream& operator<<(std::ostream& os, const vec& v) {
    int n = v.size();
    if (n <= 200){
    os << "{";
    for (int i = 0; i + 1 < n;++i){
    os << v[i] << ", ";
    }
    os << v[int(n - 1)] << "}";
    }
return os;}; // Prints coordinates for <<

vec operator-(const vec& v){ // Change of sign of a vector
    int n = v.size();
    vec u(n);
    for (int i = 0; i < n;++i){u[i] = -v[i];}
    return u;
}
vec operator-(const vec& v, const vec& w){ // Subtraction between vectors
    int n = v.size();
    if (n != w.size()) {throw std::runtime_error("Dimension mismatch");}
    vec u(n);
    for (int i = 0; i < n;++i){u[i] = v[i] - w[i];}
    return u;
}
vec operator-(const vec& v, const double a){ // Subtraction of constant 
    int n = v.size();
    vec u(n);
    for (int i = 0; i < n;++i){u[i] = v[i] - a;}
    return u;
}
vec operator-(const double a, const vec& v){ // Subtraction of a vector to a constant
    int n = v.size();
    vec u(n);
    for (int i = 0; i < n;++i){u[i] = -v[i] + a;}
    return u;
}

vec operator+(const vec& v, const vec& w){ // Addition of vectors
    int n = v.size();
    if (n != w.size()) {throw std::runtime_error("Dimension mismatch");}
    vec u(n);
    for (int i = 0; i < n;++i){u[i] = v[i] + w[i];}
    return u;
}
vec operator+(const vec& v, const double a){ // Addition of a constant
    int n = v.size();
    vec u(n);
    for (int i = 0; i < n;++i){u[i] = v[i] + a;}
    return u;
}
vec operator+(const double a, const vec& v){ // Addition of a constant
    int n = v.size();
    vec u(n);
    for (int i = 0; i < n;++i){u[i] = v[i] + a;}
    return u;
}

vec operator*(const vec& v, const double a){ // Multiplication of a constant
    int n = v.size();
    vec u(n);
    for (int i = 0; i < n;++i){u[i] = v[i]*a;}
    return u;
}
vec operator*(const double a, const vec& v){ // Multiplication of a constant
    int n = v.size();
    vec u(n);
    for (int i = 0; i < n;++i){u[i] = v[i]*a;}
    return u;
}

vec operator*(const vec& v, const vec& w){ // Multiplication of a vectors
    int n = v.size();
    if (n != w.size()) {throw std::runtime_error("Dimensions of multiplied vectors mismatches");}
    vec u(n);
    for (int i = 0; i < n;++i){u[i] = v[i]*w[i];}
    return u;
}

vec operator/(const vec& v, const double a){ // Division of a constant
    int n = v.size();
    vec u(n);
    for (int i = 0; i < n;++i){u[i] = v[i]/a;}
    return u;
}

vec operator/(const vec& v, const vec& w){ // Division of a vectors
    int n = v.size();
    if (n != w.size()) {throw std::runtime_error("Dimensions of divided vectors mismatches");}
    vec u(n);
    for (int i = 0; i < n;++i){u[i] = v[i]/w[i];}
    return u;
}

double dot(const vec& v, const vec& w){ // Dot product between vectors
    int n = v.size();
    if (n != w.size()){throw std::runtime_error("Dimensions mismatch");}
    double sum = 0;
    for (int i = 0; i < n;++i){
        sum += v[i]*w[i];
    }
    return sum;
}
double norm(const vec& v){
    double sum = 0;
    for (int i = 0; i < v.size(); ++i){
        sum += v[i]*v[i];
    }
    return std::sqrt(sum);
}
vec project(const vec& v, const vec &w, bool demand_same_size){ // Projects vector onto another vector
    int n = v.size(), m = w.size();
    if (n != m && demand_same_size) {throw std::runtime_error("Dimensions mismatches");}
    int min = std::min(n, m);
    double sum = 0;
    
    for (int i = 0; i < min;++i){
        sum += v[i]*w[i];
    }
    return sum/dot(w, w)*w;
}


bool approx(double a, double b, double acc, double eps) {
        double diff = std::abs(a - b);
        if (diff <= acc) return true;  // absolute tolerance
        double max_ab = std::max(std::abs(a), std::abs(b));
        return diff <= eps * max_ab;   // relative tolerance
}

bool approx(const vec& v, const vec& w, double acc, double eps){
    int n = v.size();
    if (n != w.size()) {throw std::runtime_error("Dimensions mismatches");}
    for (int i = 0; i < n;++i){if(!approx(v[i], w[i], acc, eps)) return false;}
    return true;
}

vec arange(const double xmin, const double xmax, const double dx){
    int size = int((xmax - xmin)/dx) + 1;
    if (approx((float) size, (xmax - xmin)/dx)){size += 1;}
    vec v(size);
    for (int i = 0; i < size; ++i){
        v[i] = xmin + i * dx;
    }
    return v;
}
vec linspace(const double xmin, const double xmax, const int size){
    float dx = (xmax - xmin)/size;
    vec v(size);
    for (int i = 0; i < size; ++i){
        v[i] = xmin + i * dx;
    }
    return v;
}
}