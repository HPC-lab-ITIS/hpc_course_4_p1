#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
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


    int threadsNum = 2;
    omp_set_num_threads(threadsNum);
  

#pragma omp parallel for shared(a[], b[], с[]) 
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            for(int k = 0; k < n; ++k)
                c[i*n + j] += a[i*n + k] * b[k*n + j];

    // Test correctness
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j) {
            double t = 0;
            for(int k = 0; k < n; ++k)
                t += a[i*n + k] * b[k*n + j];
            if (std::abs(t - c[i*n + j]) > 1e-16) return 1;
        }

    return 0;
}
