// qsort.cpp
#include <string.h>
#include "volsort.h"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int int_cmp(const void *a, const void *b);
int cstring_cmp(const void *a, const void *b);

void qsort_sort(List &l, bool numeric) {	
	Node* my_list[l.size];

	Node* node = l.head->next;
	int count = 0;
	while(node != nullptr){
		my_list[count] = (node);
		cout<<node->number<<endl;
		node = node->next;
	}
	
	if(numeric)	qsort(my_list, l.size, sizeof(Node), int_cmp); 
	else	qsort(my_list, l.size, sizeof(Node), cstring_cmp); 
	
	l.head->next = my_list[0];

	for(int i = 0; i < int(l.size); i++){
		if(i == int(l.size-1)){
			my_list[i]->next = NULL;
		}
		else{
			my_list[i]->next = my_list[i+1];
		}
	}
}

int int_cmp(const void *a, const void *b){
	const Node *ia = (Node *)a;
	const Node *ib = (Node *)b;
	cout<<ib->number<<"----------" <<ia->number<<endl;
	return (ia->number - ib->number);
}

int cstring_cmp(const void *a, const void *b){
	Node* ia = (Node *)a;
	Node *ib = (Node *)b;
	return strcmp(ia->string.c_str(),ib->string.c_str());
}
