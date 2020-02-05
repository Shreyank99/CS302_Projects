/* list.cpp
 * Contains constructor, destructor, and clear member functions for the List class
 */

#include "volsort.h"
#include <list>
#include <iostream>

using namespace std;

//Constructor, creates new List by creating head node and setting size to 0
List::List() {
	Node* s = new Node();
	head = s;
	head->number = 0;
	head->string = "";
	head->next = nullptr;
	size = 0;
}

//Destructor, deletes the top node and replaces it with the next until only the head is left, then deletes the head
List::~List() {
	while(size != 0){
		Node *temp = head->next;
		Node *temp2 = temp->next;
		head->next = temp2;
		delete temp;
		size--;
	}
	delete head;
}

//Clears list until it is empty nothing is left other than the head node
void List::Clear(){
	while(size != 0){
		Node *temp = head->next;
		Node *temp2 = temp->next;
		head->next = temp2;
		delete temp;
		size--;
		
	}
}
