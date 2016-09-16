#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <omp.h>

//Matrix multiplication    
int main(int argc, char *argv[])
{
    int n = 3;
    
//    int myints[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<double> a(n*n);
//    int myints2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<double> b (n*n);
    std::vector<double> c(n*n, 0);
    
    std::srand(std::time(0));
    
    std::generate(a.begin(), a.end(), std::rand);
    
    std::generate(b.begin(), b.end(), std::rand);
    
//    std::cout << "a\n";
//    for (std::vector<do>::const_iterator i = a.begin(); i != a.end(); ++i)
//        std::cout << *i << ' ';
//    std::cout << '\n';
//    
//    std::cout << "b\n";
//    for (std::vector<int>::const_iterator i = b.begin(); i != b.end(); ++i)
//        std::cout << *i << ' ';
//    std::cout << '\n';
    
    double start = omp_get_wtime();
    
    omp_set_num_threads(5);
#pragma omp parallel for
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
            for(int k = 0; k < n; ++k){
                c[i*n + j] += a[i*n + k] * b[k*n + j];
//                std::cout << (c[i*n + j]) << std::end;
//                std::cout << 123.456 << std::endl;
            }
        printf("thread num: %d, line: %d \n", omp_get_thread_num(), i);
    }
    double end = omp_get_wtime();
        printf("time %.16g \n", end - start);
    
    start = omp_get_wtime();
    
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            for(int k = 0; k < n; ++k){
                c[i*n + j] += a[i*n + k] * b[k*n + j];
                //                std::cout << (c[i*n + j]) << std::end;
                //                std::cout << 123.456 << std::endl;
            }
    
    
    end = omp_get_wtime();
    printf("time %.16g \n", end - start);
    
//    std::cout << "c\n";
//    for (std::vector<int>::const_iterator i = c.begin(); i != c.end(); ++i)
//        std::cout << *i << ' ';
//    std::cout << '\n';
//    
    return 0;
}
