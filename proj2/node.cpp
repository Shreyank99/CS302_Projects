#include "volsort.h"
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

bool node_number_compare(const Node *a, const Node *b)
{
	//cout << "here\n";
	if(a->number < b->number) return true;
	return false;
}

bool node_string_compare(const Node *a, const Node *b)
{
	if(a->string < b->string) return true;
	return false;
}

void dump_node(Node *n)
{
	Node *tmp;
	
	cout << "string: " << n->string << endl;
	cout << "number: " << n->number << endl;

	tmp = n->next;

	while(tmp != nullptr){
		cout << "string: " << tmp->string << endl;
		cout << "number: " << tmp->number << endl;

		tmp = tmp->next;
	}
	return;
}

void List::Push_Front(const std::string &s)
{

	Node *n;
	Node *tmp;
	int number;

	try{
		number = stoi(s);	
	}

	catch(std::invalid_argument& e){
		number = 0;
	}
	catch(std::out_of_range& e){
		number = 0;
	}

	n = new Node;
	n->number = number;
	//cout<<number<<endl;
	n->string = s;
	size++;

	tmp = head->next;
	head->next = n;
	n->next = tmp;


}
