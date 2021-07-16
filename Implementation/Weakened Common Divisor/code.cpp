    //https://codeforces.com/contest/1025/problem/B
    #include <bits/stdc++.h>
    using namespace std;
    typedef long long int ll;
    typedef pair<ll, ll> pi;
    #define mp make_pair
    #define pb push_back
    #define mx 2000000000
    bool s[1000000];
    vector<ll> p;
     
    void siv()
    {
    	memset(s, false, sizeof s);
    	for(ll i=2;i<=sqrt(mx);i+=2)
    	{
    		if(!s[i]) 
    		{ 
    		    p.pb(i);
        		for(ll j=i*i;j<=sqrt(mx);j=j+i)
        			s[j]=true;
        		
    		}
    		if(i==2)
    		   i--;
    	}
    }
     
    int main()
    {
    //freopen("input.txt", "r", stdin);
        //ios_base::sync_with_stdio(false);
        //cin.tie(NULL);cout.tie(NULL);
        siv();
        ll n; cin >> n;
        vector<pi> ans;
        ll a[n], b[n]; for(int i=0;i<n;i++) cin >> a[i] >> b[i];
        queue<ll> q1, q2;
     
    	for(int i=0;i<p.size();i++)
    	{
    		if(a[0]%p[i]==0 || b[0]%p[i]==0) q1.push(p[i]);
    		while(a[0]%p[i]==0) a[0]/=p[i];
    		while(b[0]%p[i]==0) b[0]/=p[i];
    	}
    	if(a[0]>1) q1.push(a[0]);
    	if(b[0]>1) q1.push(b[0]);
    	//for(auto itr=v.begin(); itr!=v.end();itr++) cout << *itr << "\n";
    	for(int i=1;i<n;i++)
    	{
    		while(!q1.empty())
    		{
    			ll tmp=q1.front(); q1.pop();
    			//cout << a[i] << " " << b[i] << " " << tmp << "\n";
    			if(a[i]%tmp==0 || b[i]%tmp==0) q2.push(tmp);
    		}
     
    		while(!q2.empty())
    		{
    			ll tmp=q2.front(); q1.push(tmp); q2.pop();
    		}
    	}
    	if(q1.size()==0) cout << "-1";
    	else
    	{
    		ll ans=q1.front(); cout << ans;
    	}
    }