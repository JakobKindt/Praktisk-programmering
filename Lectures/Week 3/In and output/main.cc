#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
int main(int argc, char** argv){ //char** is array of array of characters?
    std::vector<double> x,y;
    double number1, number2;
    std::cout << "standard out stream \n";
    std::cerr << "standard error stream \n";
    // std::cin >> token;
    while(std::cin >> number1 >> number2){ // cin, if it succeds, it returns true, else it returns false
        x.push_back(number1);
        y.push_back(number2);
    }
    std::cout << "# x, y, atan(x, y) \n";
    for (size_t i = 0; i < x.size(); i++){
        double xi = x[i];
        double yi = y[i];
        std::cout << xi << " " << yi << " " << std::atan2(xi, yi) << "\n";
    }
    std::ifstream myinput("data.txt"); // input file
    std::ofstream myoutput("out.txt"); // output file
    while (myinput >> number1 >> number2){
        myoutput << number1 << " " << number2 << "\n";
    }
return 0;
}



// int main(){
//     std::vector<double> x,y;
//     double number1, number2;
//     std::cout << "standard out stream \n";
//     std::cerr << "standard error stream \n";
//     // std::cin >> token;
//     while(std::cin >> number1 >> number2){ // cin, if it succeds, it returns true, else it returns false
//         x.push_back(number1);
//         y.push_back(number2);
//     }
//     std::cout << "# x, y, atan(x, y) \n";
//     for (size_t i = 0; i < x.size(); i++){
//         double xi = x[i];
//         double yi = y[i];
//         std::cout << xi << " " << yi << " " << std::atan2(xi, yi) << "\n";
//     }
//     std::ifstream myinput("data.txt"); // input file
//     std::ofstream myoutput("out.txt"); // output file
//     while (myinput >> number1 >> number2){
//         myoutput << number1 << " " << number2 << "\n";
//     }
// return 0;
// }
// #include<iostream>
// int main(){
//     double number;
//     std::cout << "standard out stream \n";
//     std::cerr << "standard error stream \n";
//     // std::cin >> token;
//     while(std::cin >> number){ // cin, if it succeds, it returns true, else it returns false
//     std::cout << "Got this number from std::cin " << number << "\n";
//     }
// return 0;
// }