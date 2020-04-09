#include <iostream>
using namespace std;

#include "LinkedList.h"   // include custom linked list library

int main(int argc, char *argv[]) {

  LinkedList<int> ll;  // define templated list
  int c;

  for(c=1; c<=9; c++) {   // add 1..9 inclusive to list
    cout << "appending " << c << endl;
    ll.appendNode(c);
  }

  cout << "printing." << endl;

  ll.print();   // print list

 
}

 
