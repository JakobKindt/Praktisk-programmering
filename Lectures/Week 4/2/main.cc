#include<thread>
#include<string>
#include<vector>
struct data{int start, end; double sum;};

void harm(data& p){ // &makes a reference instead of a copy such that whatever we do to data is saved even after the function has run
    int start = p.start, end = p.end;
    double sum = 0;
    for (int i = start; i< end; i++){sum += 1.0/i;}
    p.sum = sum;
}

int main(int argc, char** argv){
    int nterms = (int)1e9, nthreads = 1;
    for (int i = 0; i < argc, i++){
        std::string arg = argv[i];
        if (arg == "-terms" && i + 1 < argc){nterms = (int)std::stod(argv[++i]);} // ++i means first add then use it
        if (arg == "-threads" && i + 1 < argc){nthreads = std::stoi(argv[++i]);}
    }
    std::cerr << "terms: " << nterms << "\n";
    std::cerr << "threads: " << nthreads << "\n";

    // std::vector < std:thread > threads(nthreads);
    std::vector < std:thread > threads;
    threads.reserve(nthreads);
return 0;
}