#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <complex>
#include<vector>

namespace pp{
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
class vec {
private:
    std::vector<T> data;
public:
    vec(int n) : data(n) {};                                           // default
    // (int n, int m) : cols(n*m) {nrows = n; ncols = m;}
    vec() = default;                                           // default
    vec(const vec&) = default;                                 // copy
    vec(vec&&) = default;                                      // move
    ~vec() = default;                                          // destructor
    // explicit vec(int n): data(n) {}
    vec(std::initializer_list<T> init) : data(init){}

    // vec(std::initializer_list<T> init) : data(init){}
    // template<typename... Args>
    // vec(Args... args) : data{static_cast<T>(args)...}{}

    int size() const {return data.size();}

    const T& operator[](int i) const {return data[i];} // add that it should check the size to confirm that it is possible.
    T& operator[](int i) {return data[i];} // add that it should check the size to confirm that it is possible.

    // assignment
    vec& operator=(const vec&) = default;                     // copy assignment
    vec& operator=(vec&&) = default;                          // move assignment

    // arithmetic
    vec& operator+=(const vec& w){
        if (size() != w.size()) {throw std::runtime_error("Dimensions of added vector mismatches");}
        for (int i = 0; i < size();++i){
            data[i] += w[i];
        }
        return *this;
    }; // Addition of a vector
    vec& operator-=(const vec& w){
        if (size() != w.size()) {throw std::runtime_error("Dimensions of subtracted vector mismatches");}
        for (int i = 0; i < size();++i){
            data[i] -= w[i];
        }
        return *this;
    } // Subtraction of a vector

    vec& operator*=(const vec& w){
        if (size() != w.size()) {throw std::runtime_error("Dimensions of multiplied vector mismatches");}
        for (int i = 0; i < size();++i){
            data[i] *= w[i];
        }
        return *this;
    }; // Multiplication of a vector
    vec& operator/=(const vec& w){
        if (size() != w.size()) {throw std::runtime_error("Dimensions of divided vector mismatches");}
        for (int i = 0; i < size();++i){
            data[i] /= w[i];
        }
        return *this;
    } // Division of a vector
    
    vec& operator*=(const T a){for (int i = 0; i < size();++i){data[i] *= a;}; return *this;} // Multiplication of a scalar
    vec& operator/=(const T a){for (int i = 0; i < size();++i){data[i] /= a;}; return *this;} // Division of a scalar
    vec& operator +=(const T a){for (int i = 0; i < size();++i){data[i] += a;}; return *this;} // Addition of a scalar
    vec& operator -=(const T a){for (int i = 0; i < size();++i){data[i] -= a;}; return *this;} // substraction of a scalar

    
    // utility
    double norm(void) const{
        double sum = 0;
        for (int i = 0; i < size(); ++i){
            sum += std::pow(std::abs(data[i]), 2);
        }
        return std::sqrt(sum);
    }

    vec<T>& project(const vec<T>& w, bool demand_same_size = true){
        if (size() != w.size() && demand_same_size) {throw std::runtime_error("Dimensions mismatches");}
        int min = std::min(size(), w.size());
        T sum = 0;
        if constexpr (is_complex<T>::value){
            for (int i = 0; i < min;++i){
                sum += data[i]*std::conj(w[i]);
            }
        }
        else{
            for (int i = 0; i < min;++i){
                sum += data[i]*w[i];
            }
        }
        *this = sum/std::pow(w.norm(), 2)*w;
        return *this;
    }
    // void set(T a, T b, T c) { x = a; y = b; z = c;}
    void print(const std::string& s = ""){ // for debugging // Prints coordinates
        if (size() <= 20){
        std::cout << s << "{";
        for (int i = 0; i + 1 < size();++i){
        std::cout << data[i] << ", ";
        }
        std::cout << data[int(size() - 1)] << "} \n";
        }
    }     

    // stream output
    friend std::ostream& operator<<(std::ostream& os, const vec& v) {
        if (v.size() <= 200){
        os << "{";
        for (int i = 0; i + 1 < v.size();++i){
        os << v[i] << ", ";
        }
        os << v[int(v.size() - 1)] << "}";
        }
    return os;}; // Prints coordinates for <<

    friend vec operator-(const vec& v){ // Change of sign of a vector
        vec u(v.size());
        for (int i = 0; i < v.size();++i){u[i] = -v[i];}
        return u;
    }
    friend vec operator-(const vec& v, const vec& w){ // Subtraction between vectors
        if (v.size() != w.size()) {throw std::runtime_error("Dimension mismatch");}
        vec u(v.size());
        for (int i = 0; i < v.size();++i){u[i] = v[i] - w[i];}
        return u;
    }
    friend vec operator-(const vec& v, const T a){ // Subtraction of constant 
        vec u(v.size());
        for (int i = 0; i < v.size();++i){u[i] = v[i] - a;}
        return u;
    }
    friend vec operator-(const T a, const vec& v){ // Subtraction of a vector to a constant
        vec u(v.size());
        for (int i = 0; i < v.size();++i){u[i] = -v[i] + a;}
        return u;
    }

    friend vec operator+(const vec& v, const vec& w){ // Addition of vectors
        if (v.size() != w.size()) {throw std::runtime_error("Dimension mismatch");}
        vec u(v.size());
        for (int i = 0; i < v.size();++i){u[i] = v[i] + w[i];}
        return u;
    }
    friend vec operator+(const vec& v, const T a){ // Addition of a constant
        vec u(v.size());
        for (int i = 0; i < v.size();++i){u[i] = v[i] + a;}
        return u;
    }
    friend vec operator+(const T a, const vec& v){ // Addition of a constant
        vec u(v.size());
        for (int i = 0; i < v.size();++i){u[i] = v[i] + a;}
        return u;
    }

    friend vec operator*(const vec& v, const T a){ // Multiplication of a constant
        vec u(v.size());
        for (int i = 0; i < v.size();++i){u[i] = v[i]*a;}
        return u;
    }
    friend vec operator*(const T a, const vec& v){ // Multiplication of a constant
        vec u(v.size());
        for (int i = 0; i < v.size();++i){u[i] = v[i]*a;}
        return u;
    }

    friend vec operator*(const vec& v, const vec& w){ // Multiplication of a vectors
        if (v.size() != w.size()) {throw std::runtime_error("Dimensions of multiplied vectors mismatches");}
        vec u(v.size());
        for (int i = 0; i < v.size();++i){u[i] = v[i]*w[i];}
        return u;
    }

    friend vec operator/(const vec& v, const T a){ // Division of a constant
        vec u(v.size());
        for (int i = 0; i < v.size();++i){u[i] = v[i]/a;}
        return u;
    }

    friend vec operator/(const vec& v, const vec& w){ // Division of a vectors
        if (v.size() != w.size()) {throw std::runtime_error("Dimensions of divided vectors mismatches");}
        vec u(v.size());
        for (int i = 0; i < v.size();++i){u[i] = v[i]/w[i];}
        return u;
    }

    friend T dot(const vec<T>& v, const vec<T>& w){ // Dot product between vectors
        if (v.size() != w.size()){throw std::runtime_error("Dimensions mismatch");}
        T sum = 0;
        if constexpr (is_complex<T>::value){
            for (int i = 0; i < v.size();++i){
                sum += v[i]*std::conj(w[i]);
            }
        }
        else{
            for (int i = 0; i < v.size();++i){
                sum += v[i]*w[i];
            }
        }
        return sum;
    }
    friend T norm(const vec<T>& v){
        double sum = 0;
        for (int i = 0; i < v.size(); ++i){
            sum += std::pow(std::abs(v[i]), 2);
        }
        return std::sqrt(sum);
    }
    friend vec<T> project(const vec<T>& v, const vec<T> &w, bool demand_same_size = true){ // Projects vector onto another vector
        if (v.size() != w.size() && demand_same_size) {throw std::runtime_error("Dimensions mismatches");}
        int min = std::min(v.size(), w.size());
        T sum = 0;
        if constexpr (is_complex<T>::value){
            for (int i = 0; i < min;++i){
                sum += v[i]*std::conj(w[i]);
            }
        }
        else{
            for (int i = 0; i < min;++i){
                sum += v[i]*w[i];
            }
        }
        return sum/std::pow(w.norm(), 2)*w;
    }


    friend bool approx(const vec<T>& v, const vec<T>& w, double acc = 1e-6, double eps = 1e-6){
    if (v.size() != w.size()) {throw std::runtime_error("Dimensions mismatches");}
    for (int i = 0; i < v.size();++i){if(!approx(v[i], w[i], acc, eps)) return false;}
	return true;
    }   
};
}

// #pragma once
// #include <iostream>
// #include <string>
// #include <cmath>
// #include <complex>
// #include<vector>

// namespace pp{
// template<typename T>
// bool approx(T a, T b, double acc = 1e-9, double eps = 1e-9) {
//         T diff = std::abs(a - b);
//         if (diff <= acc) return true;  // absolute tolerance
//         T max_ab = std::max(std::abs(a), std::abs(b));
//         return diff <= eps * max_ab;   // relative tolerance
//     }
// template<typename> struct is_complex : std::false_type{};
// template<typename T> struct is_complex<std::complex<T>> : std::true_type {};

// template<typename T>
// class vec {
// private:
//     std::vector<T> data;
// public:
//     vec(int n) : data(n) {};                                           // default
//     // (int n, int m) : cols(n*m) {nrows = n; ncols = m;}
//     vec() = default;                                           // default
//     vec(const vec&) = default;                                 // copy
//     vec(vec&&) = default;                                      // move
//     ~vec() = default;                                          // destructor
//     explicit vec(size_t n): data(n) {}
//     vec(std::initializer_list<T> init) : data(init){}

//     // vec(std::initializer_list<T> init) : data(init){}
//     // template<typename... Args>
//     // vec(Args... args) : data{static_cast<T>(args)...}{}

//     size_t size() const {return data.size();}

//     const T& operator[](size_t i) const {return data[i];} // add that it should check the size to confirm that it is possible.
//     T& operator[](size_t i) {return data[i];} // add that it should check the size to confirm that it is possible.

//     // assignment
//     vec& operator=(const vec&) = default;                     // copy assignment
//     vec& operator=(vec&&) = default;                          // move assignment

//     // arithmetic
//     vec& operator+=(const vec& w){
//         if (size() != w.size()) {throw std::runtime_error("Dimensions of added vector mismatches");}
//         for (size_t i = 0; i < size();++i){
//             data[i] += w[i];
//         }
//         return *this;
//     }; // Addition of a vector
//     vec& operator-=(const vec& w){
//         if (size() != w.size()) {throw std::runtime_error("Dimensions of subtracted vector mismatches");}
//         for (size_t i = 0; i < size();++i){
//             data[i] -= w[i];
//         }
//         return *this;
//     } // Subtraction of a vector

//     vec& operator*=(const vec& w){
//         if (size() != w.size()) {throw std::runtime_error("Dimensions of multiplied vector mismatches");}
//         for (size_t i = 0; i < size();++i){
//             data[i] *= w[i];
//         }
//         return *this;
//     }; // Multiplication of a vector
//     vec& operator/=(const vec& w){
//         if (size() != w.size()) {throw std::runtime_error("Dimensions of divided vector mismatches");}
//         for (size_t i = 0; i < size();++i){
//             data[i] /= w[i];
//         }
//         return *this;
//     } // Division of a vector
    
//     vec& operator*=(const T a){for (size_t i = 0; i < size();++i){data[i] *= a;}; return *this;} // Multiplication of a scalar
//     vec& operator/=(const T a){for (size_t i = 0; i < size();++i){data[i] /= a;}; return *this;} // Division of a scalar
//     vec& operator +=(const T a){for (size_t i = 0; i < size();++i){data[i] += a;}; return *this;} // Addition of a scalar
//     vec& operator -=(const T a){for (size_t i = 0; i < size();++i){data[i] -= a;}; return *this;} // substraction of a scalar

    
//     // utility
//     double norm(void) const{
//         double sum = 0;
//         for (size_t i = 0; i < size(); ++i){
//             sum += std::pow(std::abs(data[i]), 2);
//         }
//         return std::sqrt(sum);
//     }

//     vec<T>& project(const vec<T>& w, bool demand_same_size = true){
//         if (size() != w.size() && demand_same_size) {throw std::runtime_error("Dimensions mismatches");}
//         long unsigned int min = std::min(size(), w.size());
//         T sum = 0;
//         if constexpr (is_complex<T>::value){
//             for (size_t i = 0; i < min;++i){
//                 sum += data[i]*std::conj(w[i]);
//             }
//         }
//         else{
//             for (size_t i = 0; i < min;++i){
//                 sum += data[i]*w[i];
//             }
//         }
//         *this = sum/std::pow(w.norm(), 2)*w;
//         return *this;
//     }
//     // void set(T a, T b, T c) { x = a; y = b; z = c;}
//     void print(const std::string& s = ""){ // for debugging // Prints coordinates
//         if (size() <= 20){
//         std::cout << s << "{";
//         for (size_t i = 0; i + 1 < size();++i){
//         std::cout << data[i] << ", ";
//         }
//         std::cout << data[int(size() - 1)] << "} \n";
//         }
//     }     

//     // stream output
//     friend std::ostream& operator<<(std::ostream& os, const vec& v) {
//         if (v.size() <= 20){
//         os << "{";
//         for (size_t i = 0; i + 1 < v.size();++i){
//         os << v[i] << ", ";
//         }
//         os << v[int(v.size() - 1)] << "}";
//         }
//     return os;}; // Prints coordinates for <<

//     friend vec operator-(const vec& v){ // Change of sign of a vector
//         vec u(v.size());
//         for (size_t i = 0; i < v.size();++i){u[i] = -v[i];}
//         return u;
//     }
//     friend vec operator-(const vec& v, const vec& w){ // Subtraction between vectors
//         if (v.size() != w.size()) {throw std::runtime_error("Dimension mismatch");}
//         vec u(v.size());
//         for (size_t i = 0; i < v.size();++i){u[i] = v[i] - w[i];}
//         return u;
//     }
//     friend vec operator-(const vec& v, const T a){ // Subtraction of constant 
//         vec u(v.size());
//         for (size_t i = 0; i < v.size();++i){u[i] = v[i] - a;}
//         return u;
//     }
//     friend vec operator-(const T a, const vec& v){ // Subtraction of a vector to a constant
//         vec u(v.size());
//         for (size_t i = 0; i < v.size();++i){u[i] = -v[i] + a;}
//         return u;
//     }

//     friend vec operator+(const vec& v, const vec& w){ // Addition of vectors
//         if (v.size() != w.size()) {throw std::runtime_error("Dimension mismatch");}
//         vec u(v.size());
//         for (size_t i = 0; i < v.size();++i){u[i] = v[i] + w[i];}
//         return u;
//     }
//     friend vec operator+(const vec& v, const T a){ // Addition of a constant
//         vec u(v.size());
//         for (size_t i = 0; i < v.size();++i){u[i] = v[i] + a;}
//         return u;
//     }
//     friend vec operator+(const T a, const vec& v){ // Addition of a constant
//         vec u(v.size());
//         for (size_t i = 0; i < v.size();++i){u[i] = v[i] + a;}
//         return u;
//     }

//     friend vec operator*(const vec& v, const T a){ // Multiplication of a constant
//         vec u(v.size());
//         for (size_t i = 0; i < v.size();++i){u[i] = v[i]*a;}
//         return u;
//     }
//     friend vec operator*(const T a, const vec& v){ // Multiplication of a constant
//         vec u(v.size());
//         for (size_t i = 0; i < v.size();++i){u[i] = v[i]*a;}
//         return u;
//     }

//     friend vec operator*(const vec& v, const vec& w){ // Multiplication of a vectors
//         if (v.size() != w.size()) {throw std::runtime_error("Dimensions of multiplied vectors mismatches");}
//         vec u(v.size());
//         for (size_t i = 0; i < v.size();++i){u[i] = v[i]*w[i];}
//         return u;
//     }

//     friend vec operator/(const T a, const vec& v){ // Division of a constant
//         vec u(v.size());
//         for (size_t i = 0; i < v.size();++i){u[i] = v[i]/a;}
//         return u;
//     }

//     friend vec operator/(const vec& v, const vec& w){ // Division of a vectors
//         if (v.size() != w.size()) {throw std::runtime_error("Dimensions of divided vectors mismatches");}
//         vec u(v.size());
//         for (size_t i = 0; i < v.size();++i){u[i] = v[i]/w[i];}
//         return u;
//     }

//     friend T dot(const vec<T>& v, const vec<T>& w){ // Dot product between vectors
//         if (v.size() != w.size()){throw std::runtime_error("Dimensions mismatch");}
//         T sum = 0;
//         if constexpr (is_complex<T>::value){
//             for (size_t i = 0; i < v.size();++i){
//                 sum += v[i]*std::conj(w[i]);
//             }
//         }
//         else{
//             for (size_t i = 0; i < v.size();++i){
//                 sum += v[i]*w[i];
//             }
//         }
//         return sum;
//     }
//     friend T norm(const vec<T>& v){
//         double sum = 0;
//         for (size_t i = 0; i < v.size(); ++i){
//             sum += std::pow(std::abs(v[i]), 2);
//         }
//         return std::sqrt(sum);
//     }
//     friend vec<T> project(const vec<T>& v, const vec<T> &w, bool demand_same_size = true){ // Projects vector onto another vector
//         if (v.size() != w.size() && demand_same_size) {throw std::runtime_error("Dimensions mismatches");}
//         long unsigned int min = std::min(v.size(), w.size());
//         T sum = 0;
//         if constexpr (is_complex<T>::value){
//             for (size_t i = 0; i < min;++i){
//                 sum += v[i]*std::conj(w[i]);
//             }
//         }
//         else{
//             for (size_t i = 0; i < min;++i){
//                 sum += v[i]*w[i];
//             }
//         }
//         return sum/std::pow(w.norm(), 2)*w;
//     }


//     friend bool approx(const vec<T>& v, const vec<T>& w, double acc = 1e-6, double eps = 1e-6){
//     if (v.size() != w.size()) {throw std::runtime_error("Dimensions mismatches");}
//     for (size_t i = 0; i < v.size();++i){if(!approx(v[i], w[i], acc, eps)) return false;}
// 	return true;
//     }   
// };
// }