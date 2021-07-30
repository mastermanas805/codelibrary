#include<bits/stdc++.h>
using namespace std;
// #define int long long
#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define pii pair<int,int>
//Huffman code

class node
{
public:
    int val;
    bool type;
    char name;
    node *left,*right,*root;
    node(int n,node *r=NULL,node *rt = NULL, bool t = false, char s = '0')
    {
        val = n;
        right=r;
        root = rt;
        type = t;
        if(type)
        {
            name = s;
            left = right = NULL;
        }
       
    }

    
};


class adaptive_huffman
{

    node *dfs(char c)
    {
        node *rt = this->root, *curr;
        stack<node *> s;
        s.push(rt);

        while(!s.empty())
        {
            curr = s.top();
            s.pop();
            if(curr->type && curr->name == c)
                return curr;
            
            if(curr->left != NULL)
              s.push(curr->left);
            if(curr->right != NULL)
              s.push(curr->right);
        }

        return NULL;
    }

    void gen_tree();
    void update_value(node *src);
    void print(node *src);
    public:
    string s;
    int flag[26] = {0};
    node *root;
    vector<int> queue;
    

    adaptive_huffman(string s)
    {
        this->s = s;
        this->root = new node(0);
        this->gen_tree();
        this->print(this->root);
    }
};


void adaptive_huffman::gen_tree()
{
    node *curr = root;
    for(auto i: this->s)
    {
        if(flag[i-'a'] == 0)
          {
                  curr->left = new node(0, NULL, curr, 0);
                  curr->right = new node(1, NULL, curr, true, i);
                  this->update_value(curr);
                  curr = !curr->left->type? curr->left: curr->right;
                  flag[i-'a'] = 1;
          }
        else
         {
             node *n = dfs(i);
             n->val++;
             this->update_value(n->root);
         }
    }
}

void adaptive_huffman::print(node* src)
{
    if(src == NULL)
       return;

    if(src->type)
    {
        cout<<src->name<<"   ";
        for(auto i:queue)
            cout<<i;
        cout<<endl;
    }

    queue.push_back(0);
    this->print(src->left);
    queue.pop_back();
    queue.push_back(1);
    this->print(src->right);
    queue.pop_back();

}


void::adaptive_huffman:: update_value(node *src)
{
    if(src == NULL)
        return;
    
    src->val++;
    if(!src->type && src->left->val > src->right->val)
     {
         node *temp = src->left;
         src->left = src->right;
         src->right = temp;
     }
     update_value(src->root);
}



int main()
{
    string s;
    cin>>s;
    int n = s.size();
    if(!n)
      cout<<"Enter a valid string";
    else
     adaptive_huffman a(s);
}

