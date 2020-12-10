#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char * argv[]) {
  int niter = 1000000;
  int myid; 
  double x, y; 
  int i,nprocs;
  int count = 0;
  double z; 
  double pi,wtime;
  int reducedcount; 
  
  MPI_Init(& argc, & argv);
  MPI_Comm_rank(MPI_COMM_WORLD, & myid);
  MPI_Comm_size(MPI_COMM_WORLD, & nprocs);

  wtime = MPI_Wtime();
  
  for (i = 0; i < niter; ++i) {
    x = (double) rand() / RAND_MAX;
    y = (double) rand() / RAND_MAX; 
    z = sqrt((x * x) + (y * y)); 
    if (z <= 1) {
      count++;
    }
  }

  MPI_Reduce( & count, &reducedcount,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

  wtime = MPI_Wtime( ) - wtime;
  if (myid == 0) {
    pi = ((double) reducedcount / (double) (niter * nprocs)) * 4.0;
    printf("Process id :%d\n",nprocs);
    printf("Pi: %lf\n", pi);
    printf("time: %lf\n",wtime);
  }

  MPI_Finalize();
  
  return 0;
}