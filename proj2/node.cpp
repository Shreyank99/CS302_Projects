/* node.cpp
 * Contains member functions for comparing numbers, strings, pushing to the front of the list, and dumping the nodes
 */
#include "volsort.h"
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

//Compares Node a's number value to Node b's number value, if a is less than b it returns true
bool node_number_compare(const Node *a, const Node *b)
{
	if(a->number < b->number) return true;
	return false;
}

//Compares Node a's string value to Node b's string value, if a is less than b it returns true
bool node_string_compare(const Node *a, const Node *b)
{
	if(a->string < b->string) return true;
	return false;
}

// Prints to standard output all Nodes from n to the nullptr
void dump_node(Node *n)
{
	Node *tmp;
	
	if(n == nullptr){
		cout << "this node is the nullptr\n";
		return;
	}

	cout << "string: " << n->string << endl;
	cout << "number: " << n->number << endl;

	tmp = n->next;

	//prints out all nodes after n
	while(tmp != nullptr){
		cout << "string: " << tmp->string << endl;
		cout << "number: " << tmp->number << endl;

		tmp = tmp->next;
	}
	return;
}

/* Pushes s to the front of the list
 * Changes s from a string to a int 
 * the int value is stored in the new Nodes number and the string is stored in string
 */
void List::Push_Front(const std::string &s)
{

	Node *n;			//new Node to be added
	Node *tmp;			//Node that was on the top of the list
	int number;			//number to be stored in n

	//trys to convert the string to a number
	try{
		number = stoi(s);	
	}
	//if it cannot the number is stored as 0
	catch(std::invalid_argument& e){
		number = 0;
	}
	catch(std::out_of_range& e){
		number = 0;
	}

	//allocates memory for the new Node, sets its values, and increments the size
	n = new Node;
	n->number = number;
	n->string = s;
	size++;

	//n becomes the new top of the list and tmp becomes the second
	tmp = head->next;
	head->next = n;
	n->next = tmp;
	return;
}
