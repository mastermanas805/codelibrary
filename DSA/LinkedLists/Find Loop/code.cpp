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
  this->next = nullptr;
}

void addMany(LinkedList *ll, vector<int> values) {
  LinkedList *current = ll;
  while (current->next != nullptr) {
    current = current->next;
  }
  for (int value : values) {
    current->next = new LinkedList(value);
    current = current->next;
  }
}

LinkedList *getNthNode(LinkedList *ll, int n) {
  int counter = 1;
  LinkedList *current = ll;
  while (counter < n) {
    current = current->next;
    counter++;
  }
  return current;
}


LinkedList *findLoop(LinkedList *head) {
	
	LinkedList* s, *f;
	s = head->next;
	f = s->next;
	while(s != f)
	{
		
		s=s->next;
		f = f->next->next;
	}
	
    s = head;
	while(s != f)
	{
		s = s->next;
		f= f->next;
	}
	
  return s;
}

class ProgramTest  {
public:
  void Run() {
    
      LinkedList test(0);
      addMany(&test, {1, 2, 3, 4, 5, 6, 7, 8, 9});
      getNthNode(&test, 10)->next = getNthNode(&test, 5);
      cout<<findLoop(&test);
  }
};

int main()
{
    ProgramTest p;
    p.Run();
}