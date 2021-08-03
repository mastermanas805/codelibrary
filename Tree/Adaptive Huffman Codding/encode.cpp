#include<bits/stdc++.h>
using namespace std;
// #define int long long
#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define pii pair<int,int>
#define charcount 26
int ptr = charcount ==26? 'a': 0;
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

    void gen_tree();
    void update_value(node *src);
    void print_encoding();
    public:
    string s, *encode;
    int flag[charcount] = {0};
    node *root;
    vector<int> queue;
    string nytflag[charcount];
    node *addr[charcount];
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
        if(flag[i-ptr] == 0)
          {
                  this->nytflag[i-ptr] = this->nytstring(this->root, "");
                  this->flag[i-ptr] = 1;
                  curr->type = 2;
                  curr->left = new node(0, NULL, curr, 0);
                  curr->right = new node(1, NULL, curr, 1, i);
                  this->addr[i-ptr] = curr->right;
                  this->update_value(curr);
                  curr = curr->left->type != 1? curr->left: curr->right;
                  
          }
        else
         {
             node *n = this->addr[i-ptr];
             n->val++;
             this->update_value(n->root);
         }
    }
}

void adaptive_huffman::print_encoding()
{
    this->encode = new string[this->s.size()];
    string s = this->s;
    bool flag[charcount] = {0};
    int e = log2(charcount), r = charcount - (1<<(e));
    
    for(int i = 0; i < s.size(); i++)
    {
        if(!flag[s[i]-ptr])
        {
            flag[s[i]-ptr] = 1;
            if((s[i]-ptr+1) >= 1 && (s[i]-ptr+1) <= 2*r)
            {
                string x = inttobinart(s[i]-ptr);
                while(x.length() < e+1) x = "0" + x;
                cout<<s[i]<<"\t"<<this->nytflag[s[i]-ptr]+x<<endl;
            }

            else if((i - ptr + 1)> 2*r)
            {
                string x = inttobinart(s[i]-ptr - r );
                while(x.length() < e) x = "0" + x;
                cout<<s[i]<<"\t"<<this->nytflag[s[i]-ptr]+x<<endl;
            }
        }

        else
        {
            cout<<s[i]<<"\t"<<this->nytflag[s[i]-ptr] + "1"<<endl;
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
    getline(cin, s);
    int n = s.size();
    if(!n)
      cout<<"Enter a valid string";
    else
     adaptive_huffman a(s);
}

