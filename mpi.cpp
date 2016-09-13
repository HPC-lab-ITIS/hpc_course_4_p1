#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>

int main (int argc, char ** argv) 
{
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
