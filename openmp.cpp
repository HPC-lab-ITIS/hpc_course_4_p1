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
    int n = 1024;
    time_t startTime,endTime;

    std::vector<double> a(n*n);
    std::vector<double> b(n*n);
    std::vector<double> c(n*n, 0.);
    
    std::srand(std::time(0));
    
    std::generate(a.begin(), a.end(), std::rand);
    std::generate(b.begin(), b.end(), std::rand);

    time (&startTime);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            for(int k = 0; k < n; ++k)
                c[i*n + j] += a[i*n + k] * b[k*n + j];
   
    time (&endTime); 
    std::cout << difftime (endTime,startTime) << std::endl;

    time (&startTime);
    #pragma omp parallel for
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            for(int k = 0; k < n; ++k)
                c[i*n + j] += a[i*n + k] * b[k*n + j];
   
    time (&endTime); 
    std::cout << difftime (endTime,startTime) << std::endl;
    return 0;
}