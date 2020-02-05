/* quick.cpp
 * quick sorts the List
 * partitions the List into a left and right while using the frist element as the pivot
 * does so recursivly until one element is in the right or left
 * then it concatenates the left and right side together recursivly until the List is sorted
 */
#include "volsort.h"
#include <iostream>
#include <string>
using namespace std;

// Prototypes
Node *qsort(Node *top, bool numeric);
void  partition(Node *pivot, Node *&left, Node *&right, bool numeric);
Node *concatenate(Node *left, Node *right, Node *pivot);

// Implementations

//Calls recursion function that returns the new top of list
void quick_sort(List &l, bool numeric) {
	l.head->next = qsort(l.head->next, numeric);
}

/* Recursively called to sort the List
 * Calls helper functions to partition and concatenate
 * top = first element of list of nodes, used as pivot
 */
Node *qsort(Node *top, bool numeric) {

	Node *left;			//all values less than or equal to pivot
	Node *right;		//all values greater than pivot

	left = nullptr;
	right = nullptr;
	
	//partitions the list around a pivot, the pivot is the first element of the list, top
	if(top->next != nullptr)	partition(top, left, right, numeric);	

	//recursive calls to left and right lists
	if(left != nullptr) if(left->next != nullptr) left = qsort(left, numeric);
	if(right != nullptr) if(right->next != nullptr) right = qsort(right, numeric);

	//concatenates left and right lists together with the top/pivot in the middle
	return concatenate(left, right, top);
}

/* Partitions list into a left and right
 * Does so relative to the pivot
 * The current_left and current_right go down the left and right list
 * The left and right pointers passed in are the beginning of those sides
 * Current goes down the list being partitioned
 */
void partition(Node *pivot, Node *&left, Node *&right, bool numeric) {
		
	Node *current;				//used to traverse the list and move the nodes into the left and right lists	
	Node *current_left;			//current position down in the left list
	Node *current_right;		//current position down in the right list

	//pivot next must not be a nullptr to enter this function
	current = pivot->next;
	current_left = nullptr;
	current_right = nullptr;

	// Compares numbers
	if(numeric){
		while(current != nullptr){
			
			//if the current number needs to go to the left list
			if(current->number <= pivot->number){
				//if the left pointer has not been set
				if(left == nullptr){
					left = current;
					current_left = left;
				} else{
					//this happens if the start of the left has already been set
					current_left->next = current;
					current_left = current_left->next;
				}
			}
			//if the current number needs to go to the right list
			if(current->number > pivot->number){
				//if the right pointer has not been set
				if(right == nullptr){
					right = current;
					current_right = right;
				} else{
					//this happens if the start of the right has already been set
					current_right->next = current;
					current_right = current_right->next;
				}
			}
			//goes to the next element in the list
			current = current->next;
		}
		//catches if nothing was put into the left or right
		if(current_left != nullptr)	current_left->next = nullptr;
		if(current_right != nullptr) current_right->next = nullptr;
	}
	
	//Compares strings
	else{
		while(current != nullptr){
			//all actions in this else statment are the same except the below statement
			if(current->string <= pivot->string){
				
				if(left == nullptr){
					left = current;
					current_left = left;
				} else{
					current_left->next = current;
					current_left = current_left->next;
				}
			} 
			if(current->string > pivot->string){
				if(right == nullptr){
					right = current;
					current_right = right;
				} else{
					current_right->next = current;
					current_right = current_right->next;
				}
			}
			current = current->next;
		}
		if(current_left != nullptr)	current_left->next = nullptr;
		if(current_right != nullptr) current_right->next = nullptr;
	}
}

/* Concatenates the left and right lists together with the pivot in the middle
 */
Node *concatenate(Node *left, Node *right, Node *pivot) {

	Node *current;					//traverses the left list to add the pivot and right after to it

	//if left node is empty, concatenate pivot and right node
	if(left == nullptr){
		pivot->next = right;
		return pivot;
	}

	//if right node is empty, concatenate left and pivot node
	if(right == nullptr){
		current = left;
		//Loop through left node until you reach the last element and then concatenate pivot to it.
		while(current->next != nullptr) current = current->next;
		current->next = pivot;
		pivot->next = nullptr;
		return left;
	}

	//both the left and right lists had values
	//total of    left list---pivot---right list
	else{
		current = left;
		//Loop through left node until you reach the last element and then concatenate pivot to it.
		while(current->next != nullptr) current = current->next;
		current->next = pivot;
		//Concatenate pivot to right node
		current->next->next = right;
		return left;
	}
}
