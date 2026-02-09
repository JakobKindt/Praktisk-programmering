#include<iostream>
#include<fstream> // file stream
#include<string>
#include<vector>
int main(int argc, char** argv){
    std::string arg, infile = " ";
    double dr = 0.1, rmax = 10, number;
    std::vector<double> xvec;
    for (int i=0; i<argc; i++){
        arg = argv[i]; // arg is notlonger a pointer
        // std::cout << arg << "\n";
        if (arg == "-dr" && i + 1 < argc){dr = std::stod(argv[i + 1]);}
        if (arg == "-rmax" && i + 1 < argc){rmax = std::stod(argv[i + 1]);}
        if (arg=="-input" && i + 1 < argc) {infile = argv[i + 1];}
        if (arg == "-n" && i + 1 < argc){
            number = std::stod(argv[i + 1]);
            xvec.push_back(number);
        }
    }
    std::cout << "dr = " << dr << ", rmax = " << rmax << "\n";
    for (double& xi : xvec){
        std::cout << "xvec = \n" << xi << "\n";
    }
    std::ifstream myinput(infile);
    while(myinput >> number) {std::cout << "got this number: " << number << "\n";}
return 0;
}