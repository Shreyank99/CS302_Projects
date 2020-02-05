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
	Node *temp = nullptr;
  if(numeric){
    if(left->number > right->number) {
      temp = left;
      left = right;
      right = temp;
    }
  }
  else {
    if(left->string > right->string) {
      temp = left;
      left = right;
      right = temp;
    }
  }

  Node *myLeft = left;
  Node *myRight = right;

  while(myLeft->next != nullptr && myRight != nullptr) {
    if(numeric && (myLeft->next->number > myRight->number)) {
      temp = myRight->next;
      myRight->next = myLeft->next;
      myLeft->next = myRight;
      myRight = temp;
    }
    else if(!numeric && (myLeft->next->string > myRight->string)) {
      temp = myRight->next;
      myRight->next = myLeft->next;
      myLeft->next = myRight;
      myRight = temp;
    }
    myLeft = myLeft->next;
  }

  if(myLeft->next == nullptr) {
    myLeft->next = myRight;
  }

  else {
    while(myLeft->next != nullptr) {
      myLeft = myLeft -> next;
    }
    myLeft->next = myRight;
  }


  return left;
  
}
