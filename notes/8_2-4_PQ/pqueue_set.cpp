#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "pqueue.h"

/* Using a multiset to implement the priority queue makes 
   most of these methods really simple.  The first four
   here are one-liners: */

     PQueueSet::PQueueSet()    { }
void PQueueSet::Push(double d) { elements.insert(d); }
int  PQueueSet::Size()         { return elements.size(); }
bool PQueueSet::Empty()        { return elements.empty(); }

/* With Pop(), we error check, and then if the multiset
   is not empty, we return the first element, and erase
   it from the multiset. */

double PQueueSet::Pop() 
{
  multiset <double>::iterator hit;
  double retval;
  
  if (elements.empty()) {
    cerr << "Error: Called Pop on an empty PQueueSet\n";
    exit(1);
  }
  hit = elements.begin();
  retval = *hit;
  elements.erase(hit);
  return retval;
}

/* Print() is straightfoward. */

void PQueueSet::Print() 
{
  multiset <double>::iterator hit;

  for (hit = elements.begin(); hit != elements.end(); hit++) {
    if (hit != elements.begin()) cout << " ";
    cout << *hit;
  }
  cout << endl;
}
