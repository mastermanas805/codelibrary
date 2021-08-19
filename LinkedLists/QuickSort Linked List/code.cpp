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
  while(end->next != NULL) {cout<<end->value<<"->"; end = end->next;}
}

void quicksort(LinkedList *l,LinkedList *h)
{
  if(l == NULL || h == NULL || l == h) return;

  LinkedList *p = partition(l,h);
  quicksort(l,p);
  quicksort(p,h);
}

LinkedList* partition(LinkedList *l, LinkedList *h)
{
  if((l == NULL) || (h == NULL) || (l == h))  return l;

  LinkedList *pivot = h, *cur = l, *pivot_prev = l;
  cout<<(h == NULL);
  while(cur!=h)
  {
    if(cur->value < pivot->value) swap(cur,l);
    cur = cur->next;
  }
  if(cur->value > h->value) swap(cur,h);
  return cur;
}

void swap(LinkedList *a, LinkedList *b)
{
  a->value+=b->value;
  b->value= a->value - b->value;
  a->value-=b->value;
}