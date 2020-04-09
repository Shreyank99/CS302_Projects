#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include "Node.h"     // contains the node information
#include <iostream>   // for using cout

using namespace std;

template<typename T>    // templated class
class LinkedList {
 public:
  LinkedList();    // constructor
  ~LinkedList();   // deconstructor

  bool empty();                 // if the list is empty
  void print();                 // display contents of the list

 private:
  Node<T> *first;                // first element in the list
  Node<T> *newNode(const T &);   // helper function; creates a new node
};

// constructor (empty body)
template<typename T>
LinkedList<T>::LinkedList() :first(NULL) {}

// destructor -- you need to fill this in
template<typename T>
LinkedList<T>::~LinkedList() {

  }
 }
 
// predicate: is this list empty?
template<typename T>
bool LinkedList<T>::empty() { return (first == NULL); }

// utility function to create a node
template<typename T>
Node<T> *LinkedList<T>::newNode(const T &value) {
 return new Node<T>(value);
 }

// debug function for printing contents and pointer values
template<typename T>
void LinkedList<T>::print() {
 Node<T> *p=first;
 for( ; p != NULL; p = p->next) {
  cout << p->getData() << endl;
  }
 }


#endif
