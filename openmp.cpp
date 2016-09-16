#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <omp.h>
#include <time.h>


//Matrix multiplication    
int main(int argc, char *argv[])
{
    time_t start,end;
    int n = 1024;

    std::vector<double> a(n*n);
    std::vector<double> b(n*n);
    std::vector<double> c(n*n, 0.);
    
    std::srand(std::time(0));
    
    std::generate(a.begin(), a.end(), std::rand);
    std::generate(b.begin(), b.end(), std::rand);

    time (&start);
    #pragma omp parallel for shared(a,b,c,n)   
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            for(int k = 0; k < n; ++k)
                c[i*n + j] += a[i*n + k] * b[k*n + j];
	time (&end);
    double tm = difftime (end,start);
    std::cout << "Parallel time:" << std::endl;
    std::cout << tm << std::endl;
    std::cout << "=====" << std::endl;

    time (&start);  
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            for(int k = 0; k < n; ++k)
                c[i*n + j] += a[i*n + k] * b[k*n + j];
    time (&end);
    tm = difftime (end,start);
    std::cout << "Sequential time:" << std::endl;
    std::cout << tm << std::endl;
    return 0;
}
