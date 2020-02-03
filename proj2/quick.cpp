// quick.cpp

#include "volsort.h"

#include <iostream>
#include <string>

using namespace std;
// Prototypes

Node *qsort(Node *head, bool numeric);
void  partition(Node *head, Node *pivot, Node *&left, Node *&right, bool numeric);
Node *concatenate(Node *left, Node *right);

// Implementations

void quick_sort(List &l, bool numeric) {
	Node* tmp = l.head->next;
	l.head->next = qsort(tmp, numeric);
//	tmp = l.head;
//	cout << endl;
//	while(tmp != nullptr){
//		cout<<tmp->number<<" ";
//		tmp = tmp->next;
//	}
//	cout<<"end of quick_sort\n";
	
}



Node *qsort(Node *head, bool numeric) {
		
	Node * left;
	Node * right;
	Node * tmp = head->next;
	int tmp_num = 0;
	tmp_num += tmp->number;
	while(tmp != nullptr){
		if(tmp->next == nullptr)
		{
			tmp_num += tmp->number;
		}
		tmp = tmp->next;
	}

	tmp_num = int(tmp_num/2);
	Node * pivot = new Node();
	pivot->number = tmp_num;
	pivot->string = to_string(tmp_num);
	pivot->next = nullptr;
	cout<<"---------------"<<pivot->number<<endl;

	partition(head, pivot, left, right, numeric);	
	//cout<<endl;
	//cout<<endl;
	//cout<<left->next->number<<"-----"<<right->next->number<<endl;
	
	if(left->next->next != nullptr){
		left->next = qsort(left->next, numeric);
	}
	if(right->next->next != nullptr){
		right->next = qsort(right->next, numeric);
	}
	//cout<<left->next->number<<"-------!!!!--------"<<right->next->number<<endl;
	return concatenate(left, right);
}

void partition(Node *head, Node *pivot, Node *&left, Node *&right, bool numeric) {
	if(numeric){
		Node * tmp1 = left;
		Node * tmp2 = right;
		while(head != nullptr){
			cout<<head->number<<"-----"<<pivot->number<<endl;
			if(head->number <= pivot->number){				
				left->next = head;
				//left->next->next = nullptr;
				if(head->next != nullptr)	left = left->next;
				else	right->next = nullptr;
				head = head->next;
			}
			else{
				right->next = head;
				if(head->next != nullptr)	right = right->next;
				else{
					left->next = nullptr;
				}
				head = head->next;
			}
		}
		right = tmp2;
		left = tmp1;
//		cout << right->next->number<< " ";
//		cout << left->next->number<<endl;;
	}
}

Node *concatenate(Node *left, Node *right) {	
	Node * tmp = left->next;
	
	while(left->next != nullptr){
		cout<<left->number<<" ";
		left = left->next;
	}
	left->next = right->next;
	left = right->next;
	
	
	while(left->next != nullptr){
		cout<<left->number<<" ";
		left = left->next;
	}
	left->next = nullptr;
	cout<<endl;
	return tmp;
}

