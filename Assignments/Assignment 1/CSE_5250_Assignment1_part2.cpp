#include <iostream>
#include <vector>

int main() {
	std::vector<int> vector_a = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	std::vector<int> vector_b = { 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6 };
	
	int dot_product = 0;

#pragma omp parallel for
	for (int i = 0; i < vector_a.size(); i++) {
#pragma omp critical
		{
		dot_product += vector_a[i] * vector_b[i];
		}
	}

	printf("The dot product of vector_a and vector_b is %i\n", dot_product);

	return 0;
}