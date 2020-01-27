#include "volsort.h"
#include <iostream>
using std::cout;
using std::endl;

bool node_number_compare(const Node *a, const Node *b)
{
	if(a->number == b->number) return true;
	return false;
}

/*bool node_string_compare(const Node *a, const Node *b)
{
	if(a->string == b->string) return true;
	return false;
}
*/
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

//void push_front(const std::string &s)
