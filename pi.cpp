#include <iostream>
#include <cmath>
#include <omp.h>
#include <ctime>

using namespace std;

#pragma omp parallel section
double f(double xi){
    return 4.0 / (1 + xi*xi);
}

int main() {
    int n = 1000000;
    double pi = 0;
    clock_t begin = clock();

    #pragma omp parallel for
    for(int i = 1; i <= n; i++){
        double xi = (i - 0.5) / n;
        pi += f(xi);
    }

    pi *= 1.0 / n;

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "PI= " << pi << "; Time: " << elapsed_secs << endl;

	if(float(M_PI) == float(pi))
		cout << "Near enough";
	else
		cout << "increase N iteration";
    return 0;
}


