    #include<cstdio>
    #include<vector>
    #include<algorithm>
    #include<utility>
    using namespace std;
    int main(){
    	int T;scanf("%d",&T);
    	while(T--){
    		int n,k;
    		scanf("%d%d",&n,&k);
    	
        	vector<pair<int,int>>a(n);
    		vector<int>c(n);
    	
        	for(int i=0;i<n;++i)scanf("%d",&a[i].first),a[i].second=i;
    	
        	sort(a.begin(),a.end());
    	
        	int t=0;
    	
        	for(int i=0;i<n;++i) if(i<k||a[i].first!=a[i-k].first)c[a[i].second]=++t;
    	
    		t-=t%k;
    	
        	for(int i=0;i<n;++i)
            {
    			if(c[i]>t)
                  c[i]=0;
    		
            	if(c[i])
                  c[i]=(c[i]-1)%k+1;
    		
            	printf("%d ",c[i]);
    		}
    		puts("");
    	}
    }