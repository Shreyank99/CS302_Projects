// merge.cpp

#include "volsort.h"

#include <iostream>

// Prototypes

Node *msort(Node *head, bool numeric);
void split(Node *head, Node *&left, Node *&right);
Node *merge(Node *left, Node *right, bool numeric);

// Implementations

void merge_sort(List &l, bool numeric) {
  l.head->next = msort(l.head->next, numeric);
}

Node *msort(Node *head, bool numeric) {
	if (head == nullptr || head->next == nullptr)
    return head;

  Node *left;
  Node *right;

  split(head, left, right);

  msort(left, numeric);
  msort(right, numeric);

  head = merge(left, right, numeric);

  return head;
}

void split(Node *head, Node *&left, Node *&right) {
  if(head == nullptr || head -> next == nullptr) {
    *left = *head;
    right = nullptr;
    return;
  }

  Node *tortise = head;
  Node *hare = head->next;

  while(hare != nullptr) {
    hare = hare->next;
    if(hare != nullptr) {
      tortise = tortise->next;
      hare = hare->next;
    }
  }

  *left = *head;
  *right = *(tortise->next);
}

Node *merge(Node *left, Node *right, bool numeric) {
	if(left == nullptr)
    return right;
  else if(right == nullptr)
    return left;
  
  Node *result = nullptr;

  if(left->number <= right->number) {
    result = left;
    result->next = merge(left->next, right, numeric);
  }
  else {
    result = right;
    result->next = merge(left, right->next, numeric);
  }
  return result;
}
