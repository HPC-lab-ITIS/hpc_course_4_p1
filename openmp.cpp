#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <algorithm>

//Matrix multiplication    
int main(int argc, char *argv[])
{
    int n = 1024;

    std::vector<double> a(n*n);
    std::vector<double> b(n*n);
    std::vector<double> c(n*n, 0.);
    
    std::srand(std::time(0));
    
    std::generate(a.begin(), a.end(), std::rand);
    std::generate(b.begin(), b.end(), std::rand);

    clock_t begin = clock();

    #pragma omp parallel for
    for(int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            #pragma omp parallel for num_threads(2)
            for (int k = 0; k < n; ++k)
                c[i * n + j] += a[i * n + k] * b[k * n + j];
    }
    clock_t end = clock();
    printf("%f \n", double(end - begin) / CLOCKS_PER_SEC);
	
    return 0;
}
