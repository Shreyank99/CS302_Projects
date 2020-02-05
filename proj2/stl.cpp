// stl.cpp
// nodes are coppied into a vector and sotred by the stl sort
#include "volsort.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void stl_sort(List &l, bool numeric) {	
	vector<Node*> my_list;			//stores List values in a vector
	Node* node = l.head->next;		//assumes the List is not empty, used to push nodes into vector

	//pushes the Nodes of the List onto the vector
	while(node != nullptr){
		my_list.push_back(node);
		node = node->next;
	}
	
	//typs of sort, either numericly or alphanumericly
	if(numeric)	sort(my_list.begin(), my_list.end(), node_number_compare); 
	else sort(my_list.begin(), my_list.end(), node_string_compare); 

	//loops through the vector and sets pointers to sorted positions
	l.head->next = my_list[0];
	for(int i = 0; i < int(my_list.size()); i++){
		if(i == int(my_list.size()-1)){
			my_list[i]->next = NULL;
		} else{
			my_list[i]->next = my_list[i+1];
		}
	}
}

