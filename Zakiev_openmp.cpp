#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

//Matrix multiplication    
int main(int argc, char *argv[])
{

	DWORD start = GetTickCount();
	int n = 200;

	std::vector<double> a(n*n);
	std::vector<double> b(n*n);
	std::vector<double> c(n*n, 0.);

	std::srand(std::time(0));

	std::generate(a.begin(), a.end(), std::rand);
	std::generate(b.begin(), b.end(), std::rand);

#pragma omp parallel for num_threads(8)
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			for (int k = 0; k < n; ++k)
				c[i*n + j] += a[i*n + k] * b[k*n + j];

	DWORD length = GetTickCount() - start;
	cout << "Parallel version time: " << length << "\n";

	start = GetTickCount();

	std::srand(std::time(0));

	std::generate(a.begin(), a.end(), std::rand);
	std::generate(b.begin(), b.end(), std::rand);

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			for (int k = 0; k < n; ++k)
				c[i*n + j] += a[i*n + k] * b[k*n + j];

	length = GetTickCount() - start;
	cout << "Posledovatelnii version time: " << length << "\n";
    return 0;
}
