#pragma once
#include<vector>
#include<iostream>
#include<string>
#include"vec.h"
// namespace pp{

struct matrix{
    
	pp::vec<double> cols;
    int nrows, ncols; 

	double& operator[](int i,int j){return cols[i*nrows + j];}
	double& operator()(int i,int j){return cols[i*nrows + j];}


    matrix(int n, int m) : cols(n*m) {nrows = n; ncols = m;}
    matrix() = default;                                           // default
    matrix(const matrix&) = default;                                 // copy
    matrix(matrix&&) = default;                                      // move
    ~matrix() = default;

    matrix& operator=(const matrix&) = default;
    matrix& operator=(matrix&&) = default;

    // matrix(std::initializer_list<pp::vec<double>> list) : cols(list) {};
    // vec(std::initializer_list<T> init) : data(init){}


    matrix& operator*=(double);
    matrix& operator*=(matrix&);
    matrix& operator/=(double);
    matrix& operator/=(matrix&);
    matrix& operator+=(double);
    matrix& operator+=(matrix&);
    matrix& operator-=(double);
    matrix& operator-=(matrix&);

    void print(std::string s="") const {
		std::cout<<s<<" ";
		for(const pp::vec<double> &c : cols){
            std::cout<<c<<", ";
            }
		std::cout<<"\n";
	}
};

bool dimension_check(const matrix&, const matrix&);
// #pragma once
// #include<vector>
// #include<iostream>
// #include<string>
// #include"vec.h"
// // namespace pp{

// struct matrix{
// 	std::vector< pp::vec<double> > cols;


// 	double& operator[](int i,int j){return cols[j][i];}
// 	double& operator()(int i,int j){return cols[j][i];}


//     matrix() = default;                                           // default
//     matrix(const matrix&) = default;                                 // copy
//     matrix(matrix&&) = default;                                      // move
//     ~matrix() = default;

//     matrix(std::initializer_list<pp::vec<double>> list) : cols(list) {};


//     pp::vec<double> operator[](int i){return cols[i];}
//     int cols_size() const {return cols.size();}
//     int rows_size() const {return cols[0].size();}

//     matrix& operator*=(double);
//     matrix& operator*=(matrix&);
//     matrix& operator/=(double);
//     matrix& operator/=(matrix&);
//     matrix& operator+=(double);
//     matrix& operator+=(matrix&);
//     matrix& operator-=(double);
//     matrix& operator-=(matrix&);

//     void print(std::string s="") const {
// 		std::cout<<s<<" ";
// 		for(const pp::vec<double> &c : cols){
//             std::cout<<c<<", ";
//             }
// 		std::cout<<"\n";
// 	}
// };

// bool dimension_check(const matrix&, const matrix&);