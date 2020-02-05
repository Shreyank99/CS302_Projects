// merge.cpp

#include "volsort.h"
#include <iostream>

using namespace std;

// Prototypes

Node *msort(Node *head, bool numeric);
void split(Node *head, Node *&left, Node *&right);
Node *merge(Node *left, Node *right, bool numeric);

// Implementations

void merge_sort(List &l, bool numeric) {
  //cout << "MAIN START" << endl;
  l.head->next = msort(l.head->next, numeric);
  //cout << "MAIN END" << endl;
}

Node *msort(Node *head, bool numeric) {
  //cout << "MSORT|head = " << head->number << endl;

	if (head == nullptr || head->next == nullptr) {
    //cout << "MSORT|base_case" << endl;
    return head;
  }

  Node *left;
  Node *right;

  split(head, left, right);
  
  //cout << "MSORT|left = " << left->number << endl;
  //cout << "MSORT|right = " << right->number << endl;

  left = msort(left, numeric);
  right = msort(right, numeric);

  return merge(left, right, numeric);
}

void split(Node *head, Node *&left, Node *&right) {
  Node *tortise = head;
  Node *hare = head->next;

  while(hare != nullptr) {
    hare = hare->next;
    if(hare != nullptr) {
      tortise = tortise->next;
      hare = hare->next;
    }
  }

  left = head;
  right = tortise->next;
  tortise->next = nullptr;
}

Node *merge(Node *left, Node *right, bool numeric) {
	if(left == nullptr)
    return right;
  else if(right == nullptr)
    return left;
  
  Node *result = nullptr;

  if(numeric) {
    if(left->number <= right->number) {
      result = left;
      result->next = merge(left->next, right, numeric);
    }
    else {
      result = right;
      result->next = merge(left, right->next, numeric);
    }
  }
  else {
    if(left->string <= right->string) {
      result = left;
      result->next = merge(left->next, right, numeric);
    }
    else {
      result = right;
      result->next = merge(left, right->next, numeric);
    }
  }

  return result;
}
