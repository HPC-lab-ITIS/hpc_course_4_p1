#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>

std::vector multiply(std::vector<double> a, std::vector<double> b, int n, bool isParallel) {
    double start_time = omp_get_wtime();
    std::vector<double> c(n*n, 0.);
    #pragma omp parallel for collapse(3) if(isParallel)
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            for(int k = 0; k < n; ++k)
                c[i*n + j] += a[i*n + k] * b[k*n + j];
    double run_time = omp_get_wtime() - start_time;
    printf("Execution (%s): %fs\n", isParallel ? "parallel" : "sequential", run_time);
    return c;
}

bool isResultCorrect(std::vector<double> a, std::vector<double> b, std::vector<double> c) {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            double t = 0;
            for(int k = 0; k < n; ++k)
                t += a[i*n + k] * b[k*n + j];
            if (std::abs(t - c[i*n + j]) > 1e-16) return false;
        }
    }
    return true;
}

//Matrix multiplication
int main(int argc, char *argv[])
{
    int n = 1024;

    std::vector<double> a(n*n);
    std::vector<double> b(n*n);

    std::srand(std::time(0));

    std::generate(a.begin(), a.end(), std::rand);
    std::generate(b.begin(), b.end(), std::rand);

    std::vector p = multiply(a, b, n, true);
    std::vector s = multiply(a, b, n, false);
    return (isResultCorrect(a, b, p) && isResultCorrect(a, b, s)) ? 0 : 1;
}
