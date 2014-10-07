#include "mpi.h"
#include <stdio.h>
#include <string.h>

#define LENGTH 100

int main(int argc, char **argv) {
  int my_rank; // id procesu
  int p;
  int dest;
  int tag=1;
  int source;
  MPI_Status status;
  char message[LENGTH];
  int m=100;
  int flag;

  /* start up MPI */
  MPI_Init( &argc, &argv );
  // argumenty je lepsi pouzit po MPI_Init, pokud nechceme problemy
  // zalezi podle verze...	

  /* find out process rank */
  // MPI_COMM_WORLD - magicka konstanta, kterou nemame resit
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  /* find out number of processes */
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  if (my_rank != 0) {
    /* create message */
    sprintf (message,"Greetings from process %d!",my_rank);
    dest=0;
    /* length of message is strlen(message)+1 to send '\0' */
    /* blocking send */
    // MPI_CHAR - kolik bajtu je char. Je to kvuli architekture. 
    // idealni velikost je do 1kB <- rada Socha	
    MPI_Send (message, strlen(message)+1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
  }
  else {
    /* my_rank == 0 */
    printf("There are %d processes.\n", p);
    for (source=1;source<p;) {
      /* checking if message has arrived */
      MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status);
      if (flag) {
        /* receiving message by blocking receive */
        MPI_Recv(&message, LENGTH, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        printf ("%s\n",message);
        source++;
      }
    }
  }

  /* shut down MPI */
  MPI_Finalize();
  
  return 0;
}


