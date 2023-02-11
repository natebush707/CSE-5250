#include <iostream>
#include <omp.h>
#include <string>

int main() {

    omp_set_num_threads(6);

#pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        int max_threads = omp_get_max_threads();
        
        printf("hello world from thread %i of %i max threads!\n", thread_num, max_threads);
    }

    return 0;
}