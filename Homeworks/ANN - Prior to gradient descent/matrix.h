#pragma once
#include<vector>
#include<iostream>
#include<string>
#include"vector.h"
#include <iomanip> // Necessary for std::setw and std::fixed

// namespace pp{

class matrix{
public:
	pp::vec cols;
    int nrows, ncols; 

	double& operator[](int i,int j){return cols[i*nrows + j];}
    const double& operator[](int i,int j) const {return cols[i*nrows + j];}
	double& operator()(int i,int j){return cols[i*nrows + j];}


    matrix(int n, int m) : cols(n*m) {nrows = n; ncols = m;}
    matrix() = default;                                           // default
    matrix(const matrix&) = default;                                 // copy
    matrix(matrix&&) = default;                                      // move
    ~matrix() = default;

    matrix& operator=(const matrix&) = default;
    matrix& operator=(matrix&&) = default;

    matrix(std::initializer_list<pp::vec> list){
        ncols = list.size();
        
        int i = 0;
        for (pp::vec v : list){
            if (i == 0){
                nrows = v.size();
                cols = pp::vec(ncols*nrows);
            }
            for (int j = 0; j < nrows;++j){
                cols[i*nrows + j] = v[j];
            }
            ++i;
        }

    };
    matrix& operator*=(double);
    // matrix operator*=(matrix&);
    matrix& operator/=(double);
    matrix& operator/=(matrix&);
    matrix& operator+=(double);
    matrix& operator+=(matrix&);
    matrix& operator-=(double);
    matrix& operator-=(matrix&);
    matrix T(); // transposed
    matrix reshape(int, int);

    // void print(std::string s="") const {
	// 	std::cout<< s <<" ";
	// 	for(int i = 0; i < ncols;++i){
    //         std::cout <<"\t ";
    //         for (int j = 0; j < nrows;++j){
    //         std::cout<< cols[i * nrows + j] <<", \t";
    //         }
    //         std::cout <<" \n";
    //         }
            
	// 	std::cout<<"\n";
	// }
    void print(std::string s="") const {
		std::cout<< s <<"{";
		for(int i = 0; i < ncols;++i){
            std::cout <<"{";
            for (int j = 0; j < nrows - 1;++j){
            std::cout << cols[i * nrows + j] <<", ";
            }
            std::cout << cols[i * nrows + nrows - 1] <<"}";
            if (i < ncols - 1){std::cout << "\n";}
        }
		std::cout<<"}\n";
	}

    pp::vec get_col(int);
    matrix& set_col(int, pp::vec&);
    matrix& set_col(int, double);
    pp::vec get_row(int);
    matrix& set_row(int, pp::vec&);
    matrix& set_row(int, double);
};

bool dimension_check(const matrix&, const matrix&);


matrix T(const matrix&); // transposed
matrix reshape(const matrix&, const int&, const int&);
matrix identity(const int&);
// // non-member operators

matrix operator-(const matrix&);
matrix operator-(const matrix&, const matrix&);
matrix operator-(const matrix&, const double);
matrix operator-(const double, const matrix&);
matrix operator+(const matrix&, const matrix&);
matrix operator+(const matrix&, const double);
matrix operator+(const double, const matrix&);
matrix operator*(const matrix&, double);
matrix operator*(double, const matrix&);
matrix operator*(const matrix&, const matrix&);
pp::vec operator*(const matrix&, const pp::vec&);
pp::vec operator*(const pp::vec&, const matrix&);
matrix operator/(const matrix&, double);
// double dot(const vec&, const vec&);
// double norm(const vec&);
// matrix project(const vec&, const vec&);

// approximate equality
bool approx(const matrix&, const matrix&, double acc = 1e-6, double eps = 1e-6);