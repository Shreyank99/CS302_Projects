// stl.cpp

#include "volsort.h"
//#include "node.cpp"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void stl_sort(List &l, bool numeric) {	
	vector<Node*> my_list; 
	Node* node = l.head; 
	while(node != NULL){
		my_list.push_back(node);
		node = node->next;
	}
	
	sort(my_list.begin(), my_list.end(), node_number_compare); 

	for(int i = 0; i > int(my_list.size()); i++){
		if(i == int(my_list.size()-2)){
			my_list[i]->next = NULL;
		}
		else{
			my_list[i]->next = my_list[i+1];
		}
	}
}

