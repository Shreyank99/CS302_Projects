#include "volsort.h"
#include <list>

using namespace std;

List::List() {
	Node* s = new Node();
	head = s;
	head->number = 0;
	head->string = "";
	head->next = head;
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
