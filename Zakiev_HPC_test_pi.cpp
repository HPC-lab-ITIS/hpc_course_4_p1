#define _USE_MATH_DEFINES 
#include <mpi.h>
#include <cstdio>
#include <vector>
#include <iostream>

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

double openMP_pi(int num_steps) {
	int i;
	double x, pi, sum = 0.0, step;

	step = 1.0 / (double)num_steps;

#pragma omp parallel for reduction(+:sum) private(x)
	for (i = 1; i <= num_steps; i++) {
		x = (i - 0.5) * step;
		sum = sum + 4.0 / (1.0 + x*x);
	}

	pi = step * sum;
	return pi;
}

double MPI_pi(int num_steps, int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	int rank, nproc;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nproc);

	int i;
	double x, pi, converted_num_steps;

	converted_num_steps = 1.0 / (double)num_steps;

	double localSum = 0.0;

	int begin = rank*(num_steps / nproc) + 1;
	int end = ((rank + 1)*(num_steps / nproc)) < num_steps ? ((rank + 1)*(num_steps / nproc)) : num_steps;
	if (rank == nproc - 1) {
		end = num_steps;
	}
	//std::cout << "Rank: " << rank << ", begin = " << begin << ", end = " << end << "\n";

	for (i = begin; i <= end; i++) {
		x = (i - 0.5) * converted_num_steps;
		localSum = localSum + 4.0 / (1.0 + x*x);
	}
	//std::cout << "Rank: " << rank << ", localSum = " << localSum << "\n";

	double allSum = 0.0;
	MPI_Reduce(&localSum, &allSum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	pi = converted_num_steps * allSum;
	MPI_Finalize();
	return pi;
}

void HPC_pi(int argc, char* argv[]) {
	double   d;
	int n = 1000000;

	d = openMP_pi(n);
	printf("openMP: %f\n", d);

	d = MPI_pi(n, argc, argv);
	printf("MPI: %f\n", d);

	printf("Constant from cmath: %f\n", M_PI);
}

int main(int argc, char* argv[]) {
	HPC_pi(argc,argv);

	system("pause");

	// to launch: mpiexec -n 8 HPC_test_mpi.exe
}