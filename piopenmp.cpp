#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <omp.h>

double f(double x){
    return 4/(1+x*x);
}

int main(int argc, char *argv[]){
    int n = 10240;
    double s;
    #pragma omp parallel for reduction(+:s) 
    for(int i = 1; i <= n; i++)
        s += f((i - 0.5)/n);
    double pi = s/n;
   
    std::cout << pi << std::endl;
    return 0;
}