#include<bits/stdc++.h>
using namespace std;
class MinStack {
public:
    /** initialize your data structure here. */
    stack<int> *s1,*s2;
    MinStack() {
        
       
        s1 = new stack<int>;
        s2 = new stack<int>;
    }
    
    void push(int val) {
        if(this->s1->empty() || val <= this->s2->top())
            
            this->s1->push(val), this->s2->push(val);
        
        else 
            
            this->s1->push(val);
    }
    
    void pop() {
        
        if(this->s1->top() == this->s2->top()) this->s2->pop();
        this->s1->pop();
    }
    
    int top() {
        return this->s1->top();
    }
    
    int getMin() {
        return this->s2->top();
    }
};


int main()
{
    MinStack m;
    m.push(-2);
    m.push(0);
    m.push(-1);
    cout<<m.getMin();
    
}