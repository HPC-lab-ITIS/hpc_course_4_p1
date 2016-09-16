#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <time.h>

//Matrix multiplication    
int main(int argc, char *argv[])
{

    int n = 1024;	
    time_t start, end;

    std::vector<double> a(n*n);
    std::vector<double> b(n*n);
    std::vector<double> c(n*n, 0.);

    time (&start);

    std::srand(std::time(0));
    
    std::generate(a.begin(), a.end(), std::rand);
    std::generate(b.begin(), b.end(), std::rand);

       
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            for(int k = 0; k < n; ++k)
                c[i*n + j] += a[i*n + k] * b[k*n + j];

    time (&end);

    double tim = difftime (end,start);
    ::cout << tim << std::endl;


    time (&start);

    std::srand(std::time(0));
    
    std::generate(a.begin(), a.end(), std::rand);
    std::generate(b.begin(), b.end(), std::rand);

    #pragma omp parallel for
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            for(int k = 0; k < n; ++k)
                c[i*n + j] += a[i*n + k] * b[k*n + j];

    time (&end);

    tim = difftime (end,start);
    std::cout << tim << std::endl;

}
