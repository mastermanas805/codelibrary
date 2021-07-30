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
    node *left,*right;
    node(int n,node *l=NULL,node *r=NULL, bool t = false, char s = '0')
    {
        val = n;
        left=l;
        right=r;
        type = t;
        if(type)
            name = s;
    }
};

class huffman
{
    void gen_tree();
    void print(node *src);
    public:
    int n;
    pii *freq;
    char *name;
    node *root;
    vector<int> queue;
    int bitlen = 0;
    int nodesum = 0;

    huffman(int n,pii *freq,char *name)
    {
        sort(freq,freq+n);
        this->n = n;
        this->freq = freq;
        this->name = name;
        

        node *x,*y;
        x = y = NULL;
        x = new node(this->freq[0].ff,NULL,NULL,true,this->name[this->freq[0].ss]);
        if(n>=1)
            {
                y = new node(this->freq[1].ff,NULL,NULL,true,this->name[this->freq[1].ss]);
                this->root = new node(x->val + y->val,x,y);
            }
        else
            this->root = new node(x->val,x,y);
        
        this->gen_tree();
        this->print(root);
        cout<<"Average Bit Len = "<<((double)this->bitlen/(double)this->nodesum)<<endl;
    }
};


void huffman::gen_tree()
{
    for(int i =2; i<n; i++)
    {
        node *x,*y;
        x = y = NULL;
        x = new node(this->freq[i].ff,NULL,NULL,true,this->name[this->freq[i].ss]);
        y = new node(this->freq[i].ff + root->val ,x,root);
        this->root = y;
        if(y->left->val > y->right->val)
        {
            node *temp = y->left;
            y->left = y->right;
            y->right = temp;
        }
    }
}

void huffman::print(node* src)
{
    if(src == NULL)
       return;

    if(src->type)
    {
        this->bitlen+=queue.size()*src->val;
        this->nodesum+=src->val;
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

int main()
{
    int n,x;
    cin>>n;
    int a[n];
    pii b[n];
    char s[n];

    for(int i=0; i<n; i++) cin>>s[i];
    for(int i=0; i<n; i++) {cin>>x; b[i] = mp(x,i);}

    huffman h(n,b,s);
}

/*

Input:
6
A B C D E F
50 10 30 5 3 2

Output:
A   0
C   10
B   110
D   1110
F   11110
E   11111
Average Bit Len = 1.85

*/