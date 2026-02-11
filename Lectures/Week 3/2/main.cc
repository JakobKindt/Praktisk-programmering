#include<iostream>
#include<string>

template<typename T>
void echo(const T& arg){
    std::cout << "echo: arg= " << arg << "\n";
}

template<typename T>
struct list{
    T* data;
    int size;
    T& operator[](int i){return data[i];}
    list(int n){size = n; data = new T[n];}
    ~list(){size = 0; delete[] data;}
};

template<typename T>
struct bar{
    T datum;
    void print(){std::cout<<"bar: datum = " << datum << "\n";}
};


int main(){
    echo(1);
    echo(1.235);
    echo("Hello");
    bar<int> intbar {1};
    bar<double> doublebar {1.234};
    bar<std::string> stringbar {"hello"};
    intbar.print();
    doublebar.print();
    stringbar.print();
    int n = 5;
    list<double> doublelist(n);
    doublelist[0] = 1.23;
return 0;
}