#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <time.h>


double funct(double x)
{
    return 4/(1+x*x);
};


double summ(int n)
{
    double s;
    #pragma omp parallel for
    for(int i = 0; i <= n; i++)
        s += funct((i - 0.5)/n);
    return s;
};

int main (int argc, char ** argv) 
{
    
    int n = 102432;	
    double result = (1 / double(n)) * summ(n);
    std::cout << result << std::endl;
    
};



