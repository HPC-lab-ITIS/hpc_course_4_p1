//
//  piopenmp.cpp
//  
//
//  Created by User on 16.09.16.
//
//

#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <omp.h>

using namespace std;
//wrong PI calculation
int main(int argc, char *argv[])
{
    int n;
    cin >> n;
    
    double start = omp_get_wtime();
    double pi, x;
    omp_set_num_threads(5);
#pragma omp parallel for reduction(+ : pi)
    for(int i = 1; i < n; ++i)
    {
        x = (i - 0.5) / n;
//        printf("x = %.16g \n", x);
        pi += 4 / (1 + x * x);
//        printf("pi = %.16g \n", pi/n);
    }
    double end = omp_get_wtime();
            printf("pi = %.16g \n", pi/n);

    printf("time %.16g \n", end - start);
    
    start = omp_get_wtime();
    pi = 0;
    x = 0;
    for(int i = 1; i < n; ++i)
    {
        x = (i - 0.5) / n;
//        printf("x = %.16g \n", x);
        pi += 4 / (1 + x * x);

    }
            printf("pi = %.16g \n", pi/n);
    end = omp_get_wtime();
    printf("time %.16g \n", end - start);
    return 0;
}
