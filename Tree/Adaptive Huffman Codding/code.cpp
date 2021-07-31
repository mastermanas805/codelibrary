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
    int type;
    char name;
    node *left,*right,*root;
    node(int n,node *r=NULL,node *rt = NULL, int t = 0, char s = '0')
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
    void print_encoding();
    public:
    string s, *encode;
    int flag[26] = {0};
    node *root;
    vector<int> queue;
    string nytflag[26];
    string inttobinart(int n);
    string nytstring(node*, string);
    

    adaptive_huffman(string s)
    {
        this->s = s;
        this->root = new node(0);
        this->gen_tree();
        this->print_encoding();
    }
};


void adaptive_huffman::gen_tree()
{
    node *curr = root;
    for(auto i: this->s)
    {
        if(flag[i-'a'] == 0)
          {
                  this->nytflag[i-'a'] = this->nytstring(this->root, "");
                  this->flag[i-'a'] = 1;
                  curr->type = 2;
                  curr->left = new node(0, NULL, curr, 0);
                  curr->right = new node(1, NULL, curr, 1, i);
                  this->update_value(curr);
                  curr = curr->left->type != 1? curr->left: curr->right;
                  
          }
        else
         {
             node *n = dfs(i);
             n->val++;
             this->update_value(n->root);
         }
    }
}

void adaptive_huffman::print_encoding()
{
    string s = this->s;
    bool flag[26] = {0};
    int e =4, r =10;

    for(auto i: s)
    {
        if(!flag[i-'a'])
        {
            flag[i-'a'] = 1;
            if((i-'a'+1) >= 1 && (i-'a'+1) <= 2*r)
            {
                string x = inttobinart(i-'a');
                while(x.length() < e+1) x = "0" + x;
                cout<<i<<"\t"<<this->nytflag[i-'a']+x<<endl;
            }

            else if((i - 'a' + 1)> 2*r)
            {
                string x = inttobinart(i-'a' - r );
                while(x.length() < e) x = "0" + x;
                cout<<i<<"\t"<<this->nytflag[i-'a']+x<<endl;
            }
        }

        else
        {
            cout<<i<<"\t"<<((this->nytflag[i-'a'] == "")?"1":this->nytflag[i-'a'])<<endl;
        }
    }
}


void::adaptive_huffman:: update_value(node *src)
{
    if(src == NULL)
        return;
    
    src->val++;
    if(src->type == 2 && src->left->val > src->right->val)
     {
         node *temp = src->left;
         src->left = src->right;
         src->right = temp;
     }
     update_value(src->root);
}


string adaptive_huffman:: nytstring(node* src,string s = "")
{
    if(src == NULL || src->type == 0)
      return s;
    if(src->type == 1)
      return "";
    
    string l = nytstring(src->left, s+"0");
    string r = nytstring(src->right, s+"1");

    if(l == "" && r == "")
      return "";
    if(l != "")
       return l;
    else
      return r;
}

string adaptive_huffman:: inttobinart(int n)
{
    string s = "";
    while(n)
    {
         s = (n%2 == 0?"0":"1") + s;
         n>>=1;
    }
    return s;
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

