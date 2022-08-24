int max_profit(int k, std::vector<int> p) {
    int profit = INT_MAX, x = 0,y = 0, n = p.size(),temp, dif = n - 2*k;
    int l1 = 0, r1 = k-1, l2 = (r1 + dif/2 + 1)%n, r2 = (l2 + k -1 )%n;
    
    for(int i=0; i<k; i++) x+=p[i], y+=p[(i+l2)%n];
    
    profit = x+y;
    
    for(int i=k; i<2*n; i++){
        x-=p[l1%n];
        l1++,r1++;
        x+=p[r1%n];
        
        y-=p[l2%n];
        l2++, r2++;
        y+=p[r2%n];
        
        temp = x + y;
        profit = max(profit, temp);
    }
    
    return profit;
}

