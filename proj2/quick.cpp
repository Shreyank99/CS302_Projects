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

	//cout << "qsort begin\n";

	Node *left;
	Node *right;
	Node *pivot;

	left = nullptr;
	right = nullptr;
	pivot = head;
	//cout << "head in qsort: " << head->number << endl;
	//cout << "left before anything: " << left << endl;
	if(head->next != nullptr)	partition(head, pivot, left, right, numeric);	

	//cout << "after partition\n";
	if(left != nullptr) if(left->next != nullptr) left = qsort(left, numeric);
	if(right != nullptr) if(right->next != nullptr) right = qsort(right, numeric);

	//cout << "before con call\n";
	//if(left != nullptr) cout << "left:  " << left->number << endl;
	//if(right != nullptr) cout << "right: " << right->number << endl;
	
	//cout << "call concatenate\n";
	return concatenate(left, right, pivot);
}

void partition(Node *head, Node *pivot, Node *&left, Node *&right, bool numeric) {
		
	Node *current;
	Node *current_left;
	Node *current_right;

	current = pivot->next;
	current_left = nullptr;
	current_right = nullptr;


	//cout << "PIVOT: " << pivot->number << endl;

	while(current != nullptr){
		
		//cout << endl << "CURRENT NUMBER: "<< current->number << endl;


		if(current->number <= pivot->number){
			
			if(left == nullptr){
				left = current;
				current_left = left;
				//cout << "TOP OF LEFT:   " << left->number << endl;
			} else{
				//cout << "current left:  " << current->number << endl;
				current_left->next = current;
				current_left = current_left->next;
				//cout << "TOP OF LEFT:   " << left->number << endl;
			}
		} 
		if(current->number > pivot->number){
			if(right == nullptr){
				right = current;
				current_right = right;
				//cout << "TOP OF RIGHT:  " << right->number << endl;
			} else{
				//cout << "current right: " << current->number << endl;
				current_right->next = current;
				current_right = current_right->next;
			}
		}
		//cout << "current: " << current->number << endl;
		//cout << "current next: " << current->next << endl;
		current = current->next;
	}
	if(current_left != nullptr)	current_left->next = nullptr;
	if(current_right != nullptr) current_right->next = nullptr;
	//if(left != nullptr) cout << "END LEFT:  " << left->number << endl;
	//if(right != nullptr) cout << "END RIGHT: " << right->number << endl;
	//cout << "CURRENT LAST: " << current->number << endl;
}

Node *concatenate(Node *left, Node *right, Node *pivot) {

	Node *current;

	//cout << "inside concatenate\n";

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
