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
	
	if(numeric){
		int my_list[list_size];
		while(cur_node != nullptr){
			my_list[count] = cur_node->number;
			count++;
			cur_node = cur_node->next;
		}
		qsort((void *)my_list, l.size, sizeof(int), int_cmp);

		l.Clear();
		for(int i =list_size-1; i >= 0; i--){
			l.Push_Front(to_string(my_list[i]));
		}
	}
	else{
		string my_list[list_size];
		while(cur_node != nullptr){
			my_list[count] = cur_node->string;
			count++;
			cur_node = cur_node->next;
		}
		qsort((void *)my_list, l.size, sizeof(string), cstring_cmp); 
		
		l.Clear();
		for(int i =list_size-1; i >= 0; i--){
			l.Push_Front("" + my_list[i]);
		}
	}

}

int int_cmp(const void *a, const void *b){
	int ia = (*(int* )a);
	int ib = (*(int *)b);
	return (ia- ib);
}

int cstring_cmp(const void *a, const void *b){
	string ia = (*(string *)a);
	string ib = (*(string *)b);
	return strcmp(ia.c_str(),ib.c_str());
}
