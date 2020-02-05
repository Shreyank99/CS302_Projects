// qsort.cpp
#include <string.h>
#include "volsort.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <array>

using namespace std;

int int_cmp(const void *a, const void *b);
int cstring_cmp(const void *a, const void *b);

void qsort_sort(List &l, bool numeric) {	
	Node *cur_node = l.head->next;
	int list_size = l.size;	
	int count = 0; 
	Node* my_nodes[list_size];
	while(cur_node != nullptr){
		my_nodes[count] = cur_node;
		count++;
		cur_node = cur_node->next;
	}
	if(numeric)	qsort((void *)my_nodes, l.size, sizeof(Node*), int_cmp);
	else		qsort((void *)my_nodes, l.size, sizeof(Node*), cstring_cmp);
	l.head->next = my_nodes[0];
	
	for(int i = 0; i < int(l.size); i++){
	    if(i == int(l.size-1)){
			my_nodes[i]->next = NULL;
		}
		else{
			my_nodes[i]->next = my_nodes[i+1];
		}
	}
}

int int_cmp(const void *a, const void *b){
	Node* ia = (*(Node** )a);
	Node* ib = (*(Node** )b);
	return (ia->number - ib->number);
}

int cstring_cmp(const void *a, const void *b){
	Node* ia = (*(Node **)a);
	Node* ib = (*(Node **)b);
	return strcmp(ia->string.c_str(),ib->string.c_str());
}
