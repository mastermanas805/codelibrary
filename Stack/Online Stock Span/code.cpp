/*
src - https://leetcode.com/problems/online-stock-span/
reference - https://www.youtube.com/redirect?event=video_description&redir_token=QUFFLUhqbHgxRzRSdDZ0Wjl1ZmgwUFItMXZlTW5hMEx1QXxBQ3Jtc0trQXN1RlQxZFFOMk9sZU9QcTlfT1QtVUdwaWN1Sm1IVGRFNHFQSXNkdzhTdWoyeXltZTFUN0ZjNGJERm91OWFmVjdhZW1VcFM2dmpxV2YxNVZTSlBWV3NNaTgxRnZXQkk0YXBOYVpCTzI3RlNxbFhyWQ&q=https%3A%2F%2Fwww.geeksforgeeks.org%2Fthe-stock-span-problem%2F
hindi explanation - https://www.youtube.com/watch?v=p9T-fE1g1pU&list=PL_z_8CaSLPWdeOezg68SKkeLN4-T_jNHd&index=7
*/

#define mp make_pair
#define ff first
#define ss second
class StockSpanner {
public:
    stack<pair<int,int>> s;
    int i,j;
    
    StockSpanner()
    {
     this->i = -1;
    }
    
    int next(int price) {
        this->i++;
        if(this->i == 0)
        {
            s.push(mp(price, this->i));
            return 1;
        }
        
        while(!s.empty() && s.top().ff<= price) s.pop();
        
        if(s.empty())
        {
            s.push(mp(price, this->i));
            return this->i + 1;
        }
        
        else
        {
            int x = s.top().ss + 1;
            s.push(mp(price, this->i));
            return i-x + 1;
        }
    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */