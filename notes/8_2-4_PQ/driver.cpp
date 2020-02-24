//CS302 Lecture Notes - Priority Queues
//James S. Plank
//Directory: /home/plank/cs302/Notes/PQ
//Original notes: September 18, 2009
//Modification for spring 2020: SJE (January 2020)


#include "pqueue.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;

int main(int argc, char **argv)
{
  PQueue *pq;
  int i;
  double d;

  /* Construct the proper implementation of the priority queue. */

  if (argc != 2 || (argv[1][0] != 's' && argv[1][0] != 'h')) {
    fprintf(stderr, "usage: add_5 s|h\n");
    exit(1);
  }

  switch (argv[1][0]) { 
    case 's': pq = new PQueueSet(); break;
    case 'h': pq = new PQueueHeap(); break;
    default:  exit(1);
  }

  /* Prompt for five numbers.  Push them and print the PQueue. */

  cout << "Enter five numbers.\n";

  for (i = 0; i < 5; i++) {
    if (!(cin >> d)) exit(1);
    pq->Push(d);
  }
  pq->Print();
  return 0;
}
