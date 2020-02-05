// qsort.cpp
#include <string.h>
#include "volsort.h"
#include <algorithm>
#include <iostream>
#include <array>

using namespace std;
//Prototype for comparison functions
int int_cmp(const void *a, const void *b);
int cstring_cmp(const void *a, const void *b);


void qsort_sort(List &l, bool numeric) {	
	Node *cur_node = l.head->next;
	int list_size = l.size;	
	int count = 0; 
	Node* my_nodes[list_size];
	//Copy the content of the list into array to be sorted
	while(cur_node != nullptr){
		my_nodes[count] = cur_node;
		count++;
		cur_node = cur_node->next;
	}
	if(numeric)	qsort((void *)my_nodes, l.size, sizeof(Node*), int_cmp);
	else		qsort((void *)my_nodes, l.size, sizeof(Node*), cstring_cmp);
	
	//Set the first list element to the first element of node array
	l.head->next = my_nodes[0];
	
	//Rearrange list node pointers to match sorted array nodes
	for(int i = 0; i < int(l.size); i++){
	    if(i == int(l.size-1)){
			my_nodes[i]->next = NULL;
		}
		else{
			my_nodes[i]->next = my_nodes[i+1];
		}
	}
}

//Return the difference of a->number and b->number
//If difference is greater than 0, a goes after b
//If difference is smaller than 0 or equal to, a goes before b 
int int_cmp(const void *a, const void *b){
	Node* ia = (*(Node** )a);
	Node* ib = (*(Node** )b);
	return (ia->number - ib->number);
}

//Return the difference of a->string and b->string
//If difference is greater than 0, a goes after b
//If difference is smaller than 0 or equal to, a goes before b 
int cstring_cmp(const void *a, const void *b){
	Node* ia = (*(Node **)a);
	Node* ib = (*(Node **)b);
	return strcmp(ia->string.c_str(),ib->string.c_str());
}
