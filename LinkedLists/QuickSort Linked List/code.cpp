#include <bits/stdc++.h>
using namespace std;

class LinkedList {
public:
  int value;
  LinkedList *next;

  LinkedList(int value);
};

LinkedList::LinkedList(int value) {
  this->value = value;
  this->next = NULL;
}

LinkedList* insert(int n)
{
  int val;
  LinkedList *root,*temp;
  cin>>val;
  root = new LinkedList(val);
  temp = root;
  
  while(--n) {cin>>val; temp->next = new LinkedList(val); temp = temp->next;}

  return root;
}

void quicksort(LinkedList *l,LinkedList *h);
LinkedList* partition(LinkedList *l, LinkedList *h);
void swap(LinkedList *a, LinkedList *b);

int main()
{
  int n;
  cin>>n;
  LinkedList *start = insert(n);
  LinkedList *end = start;
  while(end->next != NULL) end = end->next;
  quicksort(start, end);
  end = start;
  while(end != NULL) {cout<<end->value<<"->"; end = end->next;}
}

void quicksort(LinkedList *l,LinkedList *h)
{
  if(l == NULL || h == NULL || l == h || l == h->next) return;

  LinkedList *p = partition(l,h);
  LinkedList *prev = l;
  while(prev->next != p && prev !=p) prev=prev->next;
  quicksort(l,prev);
  quicksort(p->next,h);
}

LinkedList* partition(LinkedList *l, LinkedList *h)
{
  if((l == NULL) || (h == NULL) || (l == h))  return l;

  LinkedList  *cur = l, *pivot_prev = l;
  int pivot = h->value;
  
  while(l!=h)
  {
    if(l->value < pivot) 
    {
      pivot_prev = cur;
      swap(cur,l);
      cur = cur->next;
    }
    l= l->next;
  }
  swap(cur,h);
  return cur;
}

void swap(LinkedList *a, LinkedList *b)
{
  int x = a->value;
  a->value = b->value;
  b->value = x;
}