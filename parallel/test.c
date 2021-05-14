
#include <stdio.h>
#include <stdlib.h>

#include "mpi.h"


/*************************************************************************
*
**************************************************************************/
int main(int argc, char *argv[])
{
  int mype, npes;
  MPI_Comm comm = MPI_COMM_WORLD;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(comm, &npes);
  MPI_Comm_rank(comm, &mype);

  printf("I am %d from %d processes\n", mype, npes);
  MPI_Finalize();
  return(0);
}

