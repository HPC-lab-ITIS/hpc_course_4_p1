#include <iostream>
#include <math.h>
#include <omp.h>
#include <cstdlib>
#include <time.h>
using namespace std;

double calculatexi(int i, int n)
{
    return (i-0.5)/(double)n;
}

double calculatefi(double xi)
{
    return 4/(1+xi*xi);
}

double calculate(int n)
{
    double pi;
    double xi;
    int i;
    // remove pragma to get sequential version
    #pragma omp parallel for private(xi,i) reduction(+:pi)   
    for(i=1;i<=n;i++)
    {
        xi = calculatexi(i,n);
        pi+= calculatefi(xi);

    }

    return pi/(double)n;
}

int main(int argc, char *argv[])
{   
    time_t start,end;
    int n = atoi(argv[2]);

    time (&start);
    double result = calculate(n);
    time (&end);
    
    cout << "GOT" << endl;
    cout << result << endl;
    cout << "MATH PI" << endl;
    cout << M_PI << endl;
    
    double tm = difftime (end,start);
    cout << "PTime:" << endl;
    cout << tm << endl;
    
    return 0;
}