#include <vector>
#include <cstdlib>
#include <cstdio>
#include "disjoint.h"
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
  DisjointSet *d;
  string arg;

  int s01, s23, s45;
  int s0123, s456, s4567, s45678;
  int s012345678;

  /* Error check the command line. */
  arg = "";
  if (argc == 2) arg = argv[1];

  if (arg != "size" && arg != "height" && arg != "rank") {
    fprintf(stderr, "usage: example size|height|rank\n");
    exit(1);
  }

  /* Create the DisjointSet pointer using the proper subclass constructor. */

  switch(arg[0]) {
    case 's': d = new DisjointSetBySize(10); break;
    case 'h': d = new DisjointSetByHeight(10); break;
    case 'r': d = new DisjointSetByRankWPC(10); break;
    default: exit(1);
  }

  printf("Starting State:\n");
  d->Print();

  /* Do Union(0,1), Union(2,3) and Union(4,3) */

  s01 = d->Union(0, 1); 
  printf("Doing d->Union(0, 1).  Resulting set = %d\n", s01); 
  s23 = d->Union(2, 3); 
  printf("Doing d->Union(2, 3).  Resulting set = %d\n", s23); 
  s45 = d->Union(4, 5); 
  printf("Doing d->Union(4, 5).  Resulting set = %d\n", s45); 
  d->Print();

  /* Show how Find(0) now equals Find(1) */

  printf("Find(0) = %d  Find(1) = %d\n\n", d->Find(0), d->Find(1));

  /* Do the union of {0,1} and {2,3} */

  s0123 = d->Union(s01, s23); 
  printf("Doing d->Union(%d, %d).  Resulting set = %d\n", s01, s23, s0123); 

  /* Do the union of {4,5} and {6}, then {7}, then {8} */

  s456 = d->Union(s45, 6); 
  printf("Doing d->Union(%d, %d).  Resulting set = %d\n", s45, 6, s456);
  s4567 = d->Union(s456, 7); 
  printf("Doing d->Union(%d, %d).  Resulting set = %d\n", s456, 7, s4567);
  s45678 = d->Union(s4567, 8); 
  printf("Doing d->Union(%d, %d).  Resulting set = %d\n", s4567, 8, s45678);

  /* Show how Find(1) equals Find(2), and how Find(4) equals Find(7) */

  printf("d->Find(1) = %d\n", d->Find(1));
  printf("d->Find(2) = %d\n", d->Find(2));
  printf("d->Find(4) = %d\n", d->Find(4));
  printf("d->Find(7) = %d\n", d->Find(7));
  d->Print();

  /* Now, do the union of { 0, 1, 2, 3 } and { 4, 5, 6, 7, 8 } */

  s012345678 = d->Union(s0123, s45678); 

  printf("Doing d->Union(%d, %d).  Resulting set = %d\n", s0123, s45678, s012345678);
  d->Print();

  /* Show how Find(3) equals Find(5) equals Find(7) */

  printf("d->Find(3) = %d\n", d->Find(3));
  printf("d->Find(5) = %d\n", d->Find(5));
  printf("d->Find(7) = %d\n", d->Find(7));
  d->Print();

  printf("d->Find(0) = %d\n", d->Find(0));
  d->Print();
}
