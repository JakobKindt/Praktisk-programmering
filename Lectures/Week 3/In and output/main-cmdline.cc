#include<iostream>
#include<string>
int main(int argc, char** argv){
    std::string arg;
    for (int i=0; i<argc; i++){
        arg = argv[i]; // arg is notlonger a pointer
        std::cout << arg << "\n";
    }
return 0;
}