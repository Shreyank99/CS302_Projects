// qsort.cpp

#include "volsort.h"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void qsort_sort(List &l, bool numeric) {	
	vector<Node*> my_list;
	Node* node = l.head->next;
	while(node != nullptr){
		my_list.push_back(node);
		node = node->next;
	}
	
	if(numeric)	qsort((void*)&my_list[0], my_list.size(), sizeof(Node*),(int(*)(const void*,const void*))node_number_compare); 
	else	qsort((void*)&my_list[0], my_list.size(), sizeof(Node*),(int(*)(const void*,const void*))node_string_compare); 

	l.head->next = my_list[0];
	for(int i = 0; i < int(my_list.size()); i++){
		if(i == int(my_list.size()-1)){
			my_list[i]->next = NULL;
		}
		else{
			my_list[i]->next = my_list[i+1];
		}
	}
}

