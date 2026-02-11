#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>

int main (int argc, char* argv[]) {
	std::vector<double> numbers;
	for(int i=0;i<argc;++i){
		std::string arg=argv[i];
		if(arg=="-n" && i+1<argc)
			numbers.push_back(std::stod(argv[i+1]));
	}
    for(auto n: numbers)
        std::cout << n <<" "<< std::sin(n) <<" "<< std::cos(n) <<std::endl;
    std::cout << " Exact: sin(1) = 0.8414709, cos(1) = 0.5403 \n";
    std::cout << " Exact: sin(1) = 0.909297, cos(2) = -0.4161 \n";
    std::cout << " Exact: sin(1) = 0.14112, cos(3) = -0.98992 \n";
    std::cout << " Exact: sin(1) = -0.75680, cos(4) = -0.65364 \n";
    std::cout << " Exact: sin(5) = -0.95892, cos(5) = 0.28366 \n";

    double x;
    while( std::cin >> x ){
        std::cout << x <<" "<< std::sin(x) <<" "<< std::cos(x) << std::endl;
        }

    exit(EXIT_SUCCESS);
return 0;
}


// Part 3:
// int main (int argc, char *argv[]) {
// 	std::string infile="", outfile="";
// 	for(int i=0;i<argc;i++){
// 		std::string arg=argv[i];
// 		if(arg=="--input" && i+1 < argc) infile=argv[i+1];
// 		if(arg=="--output" && i+1 < argc) outfile=argv[i+1];
// 	}
//     std::ifstream myinput(infile);
//     std::ofstream myoutput(outfile);
//     double y;
//     if( myinput.is_open() && myoutput.is_open() ){
//         while( myinput >> y ){
//             myoutput << y <<" "<<std::sin(y)<<" "<<std::cos(y)<<std::endl;
//             }
//         }
//     else{
//         std::cerr << "Error opening files: " << infile << outfile << std::endl;
//         return EXIT_FAILURE;
//         }
//     myinput.close();
//     myoutput.close();
//     exit(EXIT_SUCCESS);
// }