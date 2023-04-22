// part1.cpp
// Nathan Bush - 007463099

#include <iostream>
#include <vector>
#include <omp.h>

// function prototypes
void PrintMatrix(std::vector<std::vector<int>>);
std::vector<std::vector<int>> BuildMatrix(int, bool);


int main()
{
    int matrixSize = 10;

    // initialize/build matrices
    std::vector<std::vector<int>> matrixA = BuildMatrix(matrixSize, false);
    std::vector<std::vector<int>> matrixB = BuildMatrix(matrixSize, true);
    std::vector<std::vector<int>> resultMatrix(matrixSize, std::vector<int>(matrixSize, 0));

    // multiply matrixA and matrixB
    for (int i = 0; i < matrixSize; i++) {
#pragma omp parallel for
        for (int j = 0; j < matrixSize; j++) {
            for (int k = 0; k < matrixSize; k++) {  
                int value = matrixA[i][k] * matrixB[k][j];
                int thread_id = omp_get_thread_num();
                printf("Thread %i calculated %i as a product.\n", thread_id, value);
#pragma omp critical 
                resultMatrix[i][j] += value;
            }
        }
    }

    // output results
    std::cout << std::endl << "Randomly Generated Matrix:" << std::endl;
    PrintMatrix(matrixA);
    std::cout << std::endl << "Resulting Matrix After Identity Multiplication:" << std::endl;
    PrintMatrix(resultMatrix);
}


// prints a square matrix to the console
void PrintMatrix(std::vector<std::vector<int>> matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}


// returns a square matrix of given size with random ints between 0-99
// if identity == true, returns an identity matrix of given size
std::vector<std::vector<int>> BuildMatrix(int size, bool identity) {
    srand(time(NULL));
    std::vector<std::vector<int>> matrix(size, std::vector<int>(size, 0));
    
    // build identity matrix
    if (identity) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i == j) {
                    matrix[i][j] = 1;
                }
            }
        }
    }

    // build random matrix
    else {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                matrix[i][j] = rand() % 100;
            }
        }
    }
    
    return matrix;
}