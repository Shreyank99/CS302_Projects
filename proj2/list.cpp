#include "volsort.h"
#include <list>
#include <iostream>

using namespace std;

List::List() {
	Node* s = new Node();
	head = s;
	head->number = 0;
	head->string = "";
	head->next = nullptr;
	size = 0;
}

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

void List::Clear(){
	while(size != 0){
		Node *temp = head->next;
		Node *temp2 = temp->next;
		head->next = temp2;
		delete temp;
		size--;
		
	}
}
