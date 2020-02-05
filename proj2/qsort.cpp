/* qsort.cpp
 * Uses qsort and void * to sort the List
 */
#include <string.h>
#include "volsort.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <array>
using namespace std;

//used by qsort 
int int_cmp(const void *a, const void *b);			//compares ints of the Nodes
int cstring_cmp(const void *a, const void *b);		//compares strings of the Nodes

void qsort_sort(List &l, bool numeric) {	
	Node *cur_node = l.head->next;		//traverses the list
	int list_size = l.size;				//lists size	
	int count = 0;						//					
	
	//if the comparison is numeric
	if(numeric){
		//stores the number values of the nodes in the array
		int my_list[list_size];
		while(cur_node != nullptr){
			my_list[count] = cur_node->number;
			count++;
			cur_node = cur_node->next;
		}
		//uses qsort to sort the array
		qsort((void *)my_list, l.size, sizeof(int), int_cmp);

		//clears the List and add pushes it in sorted order according to qsort
		l.Clear();
		for(int i =list_size-1; i >= 0; i--){
			l.Push_Front(to_string(my_list[i]));
		}
	}
	//if the comparison is alphanumeric
	else{
		//stores the string values of the nodes in the array
		string my_list[list_size];
		while(cur_node != nullptr){
			my_list[count] = cur_node->string;
			count++;
			cur_node = cur_node->next;
		}
		//uses qsort to sort the array
		qsort((void *)my_list, l.size, sizeof(string), cstring_cmp); 
		
		//clears the List and add pushes it in sorted order according to qsort
		l.Clear();
		for(int i =list_size-1; i >= 0; i--){
			l.Push_Front("" + my_list[i]);
		}
	}

}

//compares number values of Nodes a and b with help of qsort
int int_cmp(const void *a, const void *b){
	int ia = (*(int* )a);
	int ib = (*(int *)b);
	return (ia- ib);
}
//compares string values of Nodes a and b by with help of qsort
int cstring_cmp(const void *a, const void *b){
	string ia = (*(string *)a);
	string ib = (*(string *)b);
	return strcmp(ia.c_str(),ib.c_str());
}
