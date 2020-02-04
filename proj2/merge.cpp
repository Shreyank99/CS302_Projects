// merge.cpp

#include "volsort.h"

#include <iostream>

// Prototypes

Node *msort(Node *head, bool numeric);
void  split(Node *head, Node *&left, Node *&right);
Node *merge(Node *left, Node *right);

// Implementations

void merge_sort(List &l, bool numeric) {



}

Node *msort(Node *head, bool numeric) {
	Node* left;
	Node* right;

	if (head->next == nullptr || head->next->next == nullptr)
		return head;

	split(head, left, right);

	left = msort(left, numeric);
	right = msort(right, numeric);

	return merge(left, right);
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

Node *merge(Node *left, Node *right) {
	if(left == nullptr)
    return right;
  else if(right == nullptr)
    return left;
  
  Node *result = nullptr;

  if(left->number <= right->number) {
    result = left;
    result->next = merge(left->next, right);
  }
  else {
    result = right;
    result->next = merge(left, right->next);
  }
  return result;
}
