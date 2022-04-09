#include<bits/stdc++.h>
using namespace std;

class LinkedList {
public:
  int value;
  LinkedList *next;

  LinkedList(int value) {
    this->value = value;
    next = nullptr;
  }
};

LinkedList *shiftLinkedList(LinkedList *head, int k) {
  // Write your code here.
	int n = 0, count = 1;
	LinkedList *ptr = head;
	while(ptr != NULL)
	{
		n++;
		ptr = ptr->next;
	}
	
	
	if(n-(k%n) == n) return head;
	
	LinkedList *thead;
	ptr = head;
	while(count < (2*n-(k%n))%n)
	{
		ptr = ptr->next;
		count++;
	}
	
	thead = ptr->next;
	ptr->next = NULL;
	
	ptr = thead;
	while(ptr->next != NULL)
		ptr = ptr->next;
	
	ptr->next = head;
  return thead;
}
