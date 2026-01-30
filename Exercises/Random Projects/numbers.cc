#include<iostream> // for cout
#include<cmath> //For pow

float res(float a, float b){
    return a - pow(b, 2); // Note this is of course not the direct residual.
}

int count_digits(float num){
    float s_temp;
    int j_temp;
    s_temp = num;
    j_temp = 0;
    while (s_temp >= 1){
        s_temp /= 10;
        j_temp += 1;
    }
    return j_temp;
}

int main(int argc, char** argv){
    std::cout << "Code is running" << "\n";
    float n;
    try{
        n = std::abs(std::stof(argv[1]));
        std::cout << "Working with N = " << n << "\n";
        int j;
        int k;
        k = 0;
        j = count_digits(n);
        std::cout << j << "\n";
        int guess;
        float residual;
        bool scanning;
        int temp_guess;
        scanning = true;
        guess = std::abs(int(n/pow(10, j/2)));
        temp_guess = std::abs(guess);
        while (scanning){
            residual = res(n, guess);
            // temp_guess = temp_guess;
            int l;
            l = count_digits(std::abs(residual));
            if (residual < 0){
                temp_guess -= 1;
                // std::cout << "residual " << residual/10000 << "\n";
                // std::cout << "abs residual " << abs(residual/10000) << "\n";
                residual = res(n, temp_guess);
                // std::cout << "residual " << residual/10000 << "\n";
                // std::cout << "abs residual " << abs(residual/10000) << "\n";
            }
            else{
                temp_guess += 1;
                residual = res(n, temp_guess);
            }
            // std::cout << "residual " << residual << "\n";
            // std::cout << "abs residual " << std::abs(residual) << "\n";
            // std::cout << "reduced residual " << residual/100000 << "\n";
            // std::cout << "reduced abs residual " << std::abs(residual/100000) << "\n";
            l = count_digits(std::abs(residual));
            // std::cout << "l " << l << "\n";
            if (std::abs(residual)/pow(10, l) < std::abs(res(n, guess))/pow(10, l)){
                guess = temp_guess;
            }
            else{
                // std::cout << "abs residual " << std::abs(residual/pow(10, l)) << "\n";
                // std::cout << "abs residual 2 " << std::abs(res(n, guess)/pow(10, l)) << "\n";
                // std::cout << "abs residual 3 " << std::abs(residual) - std::abs(res(n, guess)) << "\n";
                scanning = false;
            }
            k += 1;
        }
        residual = n - pow(guess, 2);
        std::cout << "Closest integer for sqrt(N) is " << guess << "\n";
        std::cout << "Residual for " << guess - 1 << ": " << res(n, guess - 1) << "\n";
        std::cout << "Residual for " << guess << ": " << residual << "\n";
        std::cout << "Residual for " << guess + 1 << ": " << res(n, guess + 1) << "\n";
        std::cout << "k " << k << "\n";
    } catch(...){
        std::cout << "Please provide a number by writing make run N=4" << "\n";
    }
    std::cout << "Code is done running" << std::endl;
return 0;
}