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

	//Copy content of list into vector to be sorted
	while(node != nullptr){
		my_list.push_back(node);
		node = node->next;
	}

	//Sort list using the correct node compare function 
	if(numeric)	sort(my_list.begin(), my_list.end(), node_number_compare); 
	else	sort(my_list.begin(), my_list.end(), node_string_compare); 

	l.head->next = my_list[0];
	//Rearrange list pointers to match order of sorted vector elements
	for(int i = 0; i < int(my_list.size()); i++){
		if(i == int(my_list.size()-1)){
			my_list[i]->next = NULL;
		} else{
			my_list[i]->next = my_list[i+1];
		}
	}
}

