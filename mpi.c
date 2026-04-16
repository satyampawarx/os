


#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char **argv) {
    int rank, size;
    int i, sum = 0;
    int arr[ARRAY_SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Seed the random number generator with the rank of the process
    srand(rank);

    // Generate random numbers and store them in the array
    for (i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = rand() % 100;
    }

    // Calculate the sum of the array using MPI_Reduce
    MPI_Reduce(arr, &sum, ARRAY_SIZE, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Sum of array elements = %d\n", sum);
    }

    MPI_Finalize();

    return 0;
}




#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char **argv) {
    int rank, size;
    int i, min = 100, max = 0;
    int arr[ARRAY_SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Seed the random number generator with the rank of the process
    srand(rank);

    // Generate random numbers and store them in the array
    for (i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = rand() % 100;
    }

    // Calculate the minimum and maximum values in the array using MPI_Reduce
    MPI_Reduce(arr, &min, ARRAY_SIZE, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    MPI_Reduce(arr, &max, ARRAY_SIZE, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Minimum value in the array = %d\n", min);
        printf("Maximum value in the array = %d\n", max);
    }

    MPI_Finalize();

    return 0;
}

