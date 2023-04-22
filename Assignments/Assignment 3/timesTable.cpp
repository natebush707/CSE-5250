// CSE 5250 - Parallel Algorithms and Programming
// Programming Assignment 3: MPI Times Table
// Nathan Bush 007463099

#include <iostream>
#include <vector>
#include <iomanip>
#include <mpi.h>

using namespace std;

int main(int argc, char* argv[]) {
	int ierr;
	int rank;
	int commsize;

	ierr = MPI_Init(&argc, &argv);
	ierr = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	ierr = MPI_Comm_size(MPI_COMM_WORLD, &commsize);

	if (rank != 0) {
		// worker processes to build vectors based on rank
		std::vector<int> sendingVec;
		for (int i = 1; i < commsize; i++)
			sendingVec.push_back(rank * i);
		int size = commsize - 1;

		// send built vector
		MPI_Send(
			&sendingVec[0],
			size,
			MPI_INT,
			0,
			0,
			MPI_COMM_WORLD
		);
	} else {
		// process 0 handles workers and outputs received vectors
		for (int i = 1; i < commsize; i++) {
			std::vector<int> receivingVec;
			int size = commsize - 1;
			MPI_Status status;
			receivingVec.resize(size);

			// receive vector
			ierr = MPI_Recv(
				&receivingVec[0],
				size,
				MPI_INT,
				i,
				0,
				MPI_COMM_WORLD,
				&status
			);

			// succesful receive, output results
			if (ierr == MPI_SUCCESS) {
				for (int j = 0; j < size; j++) {
					std::cout << std::setw(4) << receivingVec[j];
				}
				std::cout << std::endl;
			}
			// failed receive, abort
			else
				MPI_Abort(MPI_COMM_WORLD, 1);
		}
	}

	ierr = MPI_Finalize();
	return 0;
}