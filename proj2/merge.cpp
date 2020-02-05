// merge.cpp

#include "volsort.h"
#include <iostream>   //for testing

using namespace std;

// Prototypes

Node *msort(Node *head, bool numeric);
void split(Node *head, Node *&left, Node *&right);
Node *merge(Node *left, Node *right, bool numeric);

// Implementations

//kicks off the merge sort
void merge_sort(List &l, bool numeric) {
  l.head->next = msort(l.head->next, numeric);
}

Node *msort(Node *head, bool numeric) {
  // checks base case
	if (head == nullptr || head->next == nullptr) {
    return head;
  }

  // get left and right sub lists
  Node *left;
  Node *right;
  split(head, left, right);
  
  // call sort on sub list
  left = msort(left, numeric);
  right = msort(right, numeric);

  // return combined lists
  return merge(left, right, numeric);
}

void split(Node *head, Node *&left, Node *&right) {
  // pointers for tortise and hare meathod
  Node *tortise = head;
  Node *hare = head->next;

  // run until hare reaches end of list
  while(hare != nullptr) {
    hare = hare->next;
    // advance tortise once per loop and hare twice
    if(hare != nullptr) {
      tortise = tortise->next;
      hare = hare->next;
    }
  }

  // return from beginning of list for left
  left = head;

  // return right of tortis for right
  right = tortise->next;

  // set nullptr to end left
  tortise->next = nullptr;
}

Node *merge(Node *left, Node *right, bool numeric) {
  // hold temp value for making swaps
	Node *temp = nullptr;

  // if the left list starts higher then the right, switch them around
  if((numeric && (left->number > right->number)) || (!numeric && (left->string > right->string))) {
    temp = left;
    left = right;
    right = temp;
  }

  // keep reference to left of list
  Node *head = left;

  // loop through left, inserting right value whenever
  //  it is lower than left until end end of one side is
  //  reached
  while(left->next != nullptr && right != nullptr) {
    if((numeric && (left->next->number > right->number)) || (!numeric && (left->next->string > right->string))) {
      temp = right->next;
      right->next = left->next;
      left->next = right;
      right = temp;
    }
    left = left->next;
  }

  // if not at the end of left, add the rest of left to the list
  if(left->next != nullptr) {
    while(left->next != nullptr) {
      left = left->next;
    }
  }

  // track right on the end of left
  left->next = right;

  // return merged list
  return head;  
}
