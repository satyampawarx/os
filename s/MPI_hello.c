#include <mpi.h>
#include <stdio.h>
int main(int argc, char** argv)
{
  MPI_Init(NULL, NULL);
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  char pname[MPI_MAX_PROCESSOR_NAME];
  int nlength;
  MPI_Get_processor_name(pname, &nlength);
  printf("Hello World from Processor %s having rank = %d out of %d processor\n",pname,rank,size);
  MPI_Finalize();
}
