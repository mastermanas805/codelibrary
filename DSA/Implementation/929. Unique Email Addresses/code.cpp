// https://leetcode.com/problems/unique-email-addresses/
class Solution {
    
    string transformPlus(string input) {
        // cout<< "input " << input << endl;
        string ret;
        
        int n =  input.length();
        bool f = 0;
        
        for ( int i=0; i < n; i++) {
            
            if ( input[i] == '@') {
                ret +=  input.substr(i, n-i);
                break;
            
            }
            
            if( f ) continue;
            
            if( input[i] == '+' ) {
                f = 1;
                continue;
            }
            
            
            ret = ret + input[i];
            
        }
        
        // cout<< ret << endl;
        return ret;
    }
    
    string transformDot(string input) {
        string ret;
        int n = input.length();
        for( int i=0; i<n; i++) {
            if ( input[i] == '@') {
                ret +=  input.substr(i, n-i);
                break;
            
            }
            if ( input[i] == '.' ) continue;
            ret += input[i];
        }
        
        // cout<< ret << endl;
        
        return ret;
    }
    
public:
    int numUniqueEmails(vector<string>& emails) {
        
        set<string> uniqueEmails;
        
        for (auto email : emails) {
            uniqueEmails.insert(transformDot(transformPlus(email)));
        }
        
        return uniqueEmails.size();
    }
};