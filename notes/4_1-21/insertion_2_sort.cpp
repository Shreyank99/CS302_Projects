/* insertion_2_sort.cpp - Insertion sort without the swapping
   James S. Plank
   CS302
   September, 2009
 */

#include <iostream>
#include <vector>
#include "sorting.h"
using namespace std;

/* I'm only commenting the differences between this and insertion_1_sort.cpp. */

void sort_doubles(vector <double> &v, int print)
{
  int i, j, k;
  double tmp;

  if (print) {
    for (j = 0; j < v.size(); j++) printf("%.2lf ", v[j]);
    cout << endl;
  }

  for (i = 1; i < v.size(); i++) {
    tmp = v[i];

    /* While v[j-1] is greater than v[i], move v[j-1] over one. */

    for (j = i; j >= 1 && tmp < v[j-1]; j--) {
      v[j] = v[j-1];
    }

    /* And put v[i] into its proper place. */

    v[j] = tmp;

    if (print) {
      for (j = 0; j < v.size(); j++) printf("%.2lf ", v[j]);
      cout << endl;
    }
  }
}

int main() {

  // added main function so it would compile                                                       

}
