#include<thread>
#include<string>
#include<vector>
#include<functional>
#include<iostream>
struct datum{int start, end; double sum;};

void harm(datum& p){ // &makes a reference instead of a copy such that whatever we do to data is saved even after the function has run
    int start = p.start, end = p.end;
    double sum = 0;
    for (int i = start; i< end; i++){sum += 1.0/i;}
    p.sum = sum;
}

int main(int argc, char** argv){
    int nterms = (int)1e9, nthreads = 1;
    for (int i = 0; i < argc; i++){
        std::string arg = argv[i];
        if (arg == "-terms" && i + 1 < argc){nterms = (int)std::stod(argv[++i]);} // ++i means first add then use it
        if (arg == "-threads" && i + 1 < argc){nthreads = std::stoi(argv[++i]);}
    }
    std::cerr << "terms: " << nterms << "\n";
    std::cerr << "threads: " << nthreads << "\n";

    // std::vector < std:thread > threads(nthreads);
    std::vector < std::thread > threads;
    threads.reserve(nthreads);
    std::vector < datum > data(nthreads);
    for (int i = 0; i < nthreads; ++i){
        data[i].start = 1 + (nterms/nthreads)*i;
        data[i].end = 1 + (nterms/nthreads)*(i + 1);
        threads.emplace_back(harm, std::ref(data[i]));
    }
    for (std::thread &thread : threads) {thread.join();}
    double total = 0;
    for (datum &d : data){total += d.sum;}
    std::cout << "total sum = " << total << "\n";
return 0;
}