#include <mpi.h>
#include <string.h>
#include <stdio.h>

const int MAX_STRING = 100;

int main(void)
{
  char greeting[MAX_STRING];
  int size;
  int rank;
  int i;
  
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  if(rank != 0)
  {
    sprintf(greeting, "Greeting from proceess %d of %d!", rank, size);
    MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
  }
  else
  {
    printf("Greeting from Master process %d of %d!\n", rank, size);
    for(i=1; i<size; i++)
    {
      MPI_Recv(greeting, MAX_STRING, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      printf("%s\n", greeting);
    }
  }
  MPI_Finalize();
  return 0;
}
