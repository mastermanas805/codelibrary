#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define forn(i,e) for(ll i = 0; i < e; i++)

void solve()
{
	ll n;
    cin>>n;
    vector<ll> A(n);
    forn(i, n) cin>>A[i];
    ll ans = 0;
    ll mx = -1;
    for(int i = n-1; i >= 1; i--)
    {
        if(A[i] > mx)
        {
            mx = A[i];
            ans++;
        }
    }
    if(A[0] >= mx)
    {
        cout<<ans<<endl;
    }
    else
    {
        cout<<-1<<endl;
    }
}

int main()
{
	ll t=1;
	cin >> t;
    forn(i,t) {
    	solve();
    }
    return 0;
}