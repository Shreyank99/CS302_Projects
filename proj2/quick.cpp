// quick.cpp

#include "volsort.h"

#include <iostream>
#include <string>

using namespace std;
// Prototypes

Node *qsort(Node *head, bool numeric);
void  partition(Node *head, Node *pivot, Node *&left, Node *&right, bool numeric);
Node *concatenate(Node *left, Node *right, Node *pivot);

// Implementations

void quick_sort(List &l, bool numeric) {
	l.head->next = qsort(l.head->next, numeric);
	
}


//Head = first element of list of nodes
Node *qsort(Node *head, bool numeric) {


	Node *left;
	Node *right;
	Node *pivot;

	left = nullptr;
	right = nullptr;
	pivot = head;
	
	if(head->next != nullptr)	partition(head, pivot, left, right, numeric);	

	if(left != nullptr) if(left->next != nullptr) left = qsort(left, numeric);
	if(right != nullptr) if(right->next != nullptr) right = qsort(right, numeric);

	return concatenate(left, right, pivot);
}

void partition(Node *head, Node *pivot, Node *&left, Node *&right, bool numeric) {
		
	Node *current;
	Node *current_left;
	Node *current_right;

	current = pivot->next;
	current_left = nullptr;
	current_right = nullptr;


	if(numeric){
		while(current != nullptr){
			
			if(current->number <= pivot->number){
				
				if(left == nullptr){
					left = current;
					current_left = left;
				} else{
					current_left->next = current;
					current_left = current_left->next;
				}
			} 
			if(current->number > pivot->number){
				if(right == nullptr){
					right = current;
					current_right = right;
				} else{
					current_right->next = current;
					current_right = current_right->next;
				}
			}
			current = current->next;
		}
		if(current_left != nullptr)	current_left->next = nullptr;
		if(current_right != nullptr) current_right->next = nullptr;
	}
	else{
		while(current != nullptr){

			if(current->string <= pivot->string){
				
				if(left == nullptr){
					left = current;
					current_left = left;
				} else{
					current_left->next = current;
					current_left = current_left->next;
				}
			} 
			if(current->string > pivot->string){
				if(right == nullptr){
					right = current;
					current_right = right;
				} else{
					current_right->next = current;
					current_right = current_right->next;
				}
			}
			current = current->next;
		}
		if(current_left != nullptr)	current_left->next = nullptr;
		if(current_right != nullptr) current_right->next = nullptr;
	}
}

Node *concatenate(Node *left, Node *right, Node *pivot) {

	Node *current;

	if(left == nullptr){
		pivot->next = right;
		return pivot;
	}
	if(right == nullptr){
		current = left;
		while(current->next != nullptr) current = current->next;
		current->next = pivot;
		pivot->next = nullptr;
		return left;
	}
	else{
		current = left;
		while(current->next != nullptr) current = current->next;
		current->next = pivot;
		current->next->next = right;
		return left;
	}
}
