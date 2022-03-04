#include<bits/stdc++.h>
using namespace std;
#define test() int t;scanf("%d",&t);for(int tno=1;tno<=t;tno++)
#define mp make_pair
#define pb push_back
#define wl(n) while(n--)
#define fi first
#define se second
#define all(c) c.begin(),c.end()
typedef long long ll;
typedef unsigned long long llu;
typedef vector<int> vi; 
typedef pair<int,int> pii;
typedef pair<int,pair<int,int> > piii ;
typedef pair<ll,ll> pll;
typedef pair<ll,int> pli;
#define sz(a) int((a).size())
#define ini(a,v) memset(a,v,sizeof(a))
#define sc(x) scanf("%d",&x)
#define sc2(x,y) scanf("%d%d",&x,&y)
#define sc3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define scl(x) scanf("%lld",&x)
#define scl2(x,y) scanf("%lld%lld",&x,&y)
#define scl3(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define scs(s) scanf("%s",s);
#define gcd __gcd
#define debug() printf("here\n") 
#define chk(a) cerr << endl << #a << " : " << a << endl
#define chk2(a,b) cerr << endl << #a << " : " << a << "\t" << #b << " : " << b << endl
#define tr(container, it)  for(typeof(container.begin()) it = container.begin(); it != container.end(); it++) 
#define MOD 1000000007
#define inf ((1<<29)-1)
#define linf ((1LL<<60)-1)
const double eps = 1e-9;

const int MAX = 200009;
ll a[MAX]={0};
ll pw(ll base ,ll expo,ll c)
{
    if(expo == 0 )
    return  1 ; 
    ll f = pw(base , expo /2,c) ; 
    if(expo&1)
    return (((f*f)%c)*base)%c ; 
    return (f*f)%c;
}
int main()
{
    int i,j,k;
    test(){
    int n;
    sc(n);
    for(i=0;i<n;i++){
        scl(a[i]);    
    }
    ll ans = 0LL;
    for(ll i=0;i<34;i++){
        ll c = 0;
        for(j=0;j<n;j++){
        if(a[j]&(1LL<<i))
            c++;
        }
        ll y = pw(2,c,MOD);
        y = (y - 1 + MOD)%MOD;
        y = (y*pw(2,i,MOD))%MOD;
        ans = (ans + y + MOD)%MOD;      
    }
    printf("%lld\n",ans);
    }
    return 0;
}

