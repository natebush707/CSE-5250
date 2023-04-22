// part2b.cpp
// Nathan Bush - 007463099

#include <iostream>
#include <set>
#include <omp.h>
#include <chrono>


int main()
{
	// initialize setup
	int maxInt = 100;
	int num_threads = 1;
	
	omp_set_num_threads(num_threads);

	// use sets to enforce uniqueness
	std::set<std::set<int>> results;

	// start timer
	auto start = std::chrono::high_resolution_clock::now();

	// find triples
#pragma omp parallel for
	for (int a = 1; a < maxInt; a++) {
#pragma omp parallel for
		for (int b = 1; b < maxInt; b++) {
#pragma omp parallel for
			for (int c = 1; c < maxInt; c++) {
				if ((a * a + b * b) + (a * b) == c * c) {
#pragma omp critical
					{
						std::set<int> triple({ a, b, c });
						results.insert(triple);
					}
				}
			}
		}
	}

	// stop timer
	auto stop = std::chrono::high_resolution_clock::now();
	auto exec_time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	// output results
	for (auto i : results) {
		std::cout << "Unique Pythagorean Triple Found: ";
		for (auto j : i) {
			std::cout << j << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << "Found pythagorean triples up to " << maxInt << " in " << exec_time.count() << " microseconds.\n" << std::endl;
}
