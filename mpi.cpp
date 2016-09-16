#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <mpi.h>

int main (int argc, char ** argv) 
{
	int rank, numprocs;
	MPI_Init (&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
    const long n = 1024*1024*16;

    std::vector<int> unsort(n);

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(1, 100);

    for(auto i = 0; i < n; ++i)
        unsort[i] = uni(rng);

	std::sort(unsort.begin(), unsort.end());

    return 0;
}
