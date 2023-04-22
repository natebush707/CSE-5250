// CSE5250Midterm.cpp - Nathan Bush

#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <omp.h>
#include <fstream>
#include <numeric>

int sieve(int, int);
std::ofstream file;

int main()
{
    int num_executions = 10;
    std::vector<int> thread_counts{ 1, 2, 4, 8, 12 };
    std::vector<int> search_maximums{ 100, 1000, 10000, 100000, 1000000, 10000000 };
    std::vector<int> times(num_executions, 0);
    
    file.open("output.txt");

    for (int thread_count : thread_counts) {
        for (int search_max : search_maximums) {
            std::cout << "Running Sieve of Eratosthenes with " << thread_count << " thread/s up to a max value of " << search_max << ".\n\n";
            file << "Running Sieve of Eratosthenes with " << thread_count << " thread/s up to a max value of " << search_max << ".\n\n";
            
            // run the sieve calculation for num_executions iterations, recording execution time
            for (int i = 0; i < num_executions; i++) {
                std::cout << "\tExecution #" << i + 1 << ": ";
                file << "\tExecution #" << i + 1 << ": ";
                times[i] = sieve(thread_count, search_max);
            }

            // calculate and report average execution time
            int avg_time = std::accumulate(times.begin(), times.end(), 0) / times.size();
            std::cout << "The average execution time after " << num_executions << " executions is " << avg_time << " microseconds.\n";
            std::cout << "----------------------\n\n";
            file << "The average execution time after " << num_executions << " executions is " << avg_time << " microseconds.\n";
            file << "----------------------\n\n";
        }
    }
}  


int sieve(int thread_count, int search_max) {
    // start timer
    auto start = std::chrono::high_resolution_clock::now();

    int sqrt_search_max = (int)sqrt(search_max);

    omp_set_num_threads(thread_count);

    std::vector<int> numbers(search_max, 0);

#pragma omp parallel for
    // initialize vector with all integers from 1 - search_max
    for (int i = 0; i < search_max; i++) {
        numbers[i] = (i + 1);
    }

    // 1 doesn't count, set the value to 0
    numbers[0] = 0;

    // perform sieve calculations
    for (int i = 0; i < sqrt_search_max; i++) {
        int current_prime = numbers[i];
        if (current_prime != 0) {
#pragma omp parallel for
            for (int j = i; j < search_max; j += current_prime) {
                int current_number = numbers[j];
                if (current_number != current_prime) {
                    numbers[j] = 0;
                }
            }
        }
    }

    // stop clock and calculate execution time
    auto stop = std::chrono::high_resolution_clock::now();
    auto exec_time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    // report results
    std::cout << "Found prime numbers up to " << search_max << " in " << exec_time.count() << " microseconds.\n\t";
    file << "Found prime numbers up to " << search_max << " in " << exec_time.count() << " microseconds.\n\t";
    for (int i = 0; i < 100; i++) {
        if (numbers[i] != 0) {
            std::cout << numbers[i] << " ";
            file << numbers[i] << " ";
        }
    }
    std::cout << std::endl << std::endl;
    file << std::endl << std::endl;

    return exec_time.count();
}