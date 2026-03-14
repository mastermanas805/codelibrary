#include <bits/stdc++.h>
using namespace std;


/*
Q1. Find the factorial of a number 'n'
*/

// 3! = 3 * 2 * 1

// '19' * 5



//.   0 9 5
//.   1 9 0

//.   2 8 5


/// Addition

// 19999
// 35560
// 05559


string Add(string s1, string s2){
  string ret;

  if(s1.length() > s2.length()){
    int dif = s1.length() - s2.length();

    for(int i=0;i<dif;i++){
      s2 = "0" + s2;
    }

  }else if(s1.length() < s2.length()){
    int dif = s2.length() - s1.length();

    for(int i=0;i<dif;i++){
      s1 = "0" + s1;
    }
  }




  int carry = 0;
  for(int i=s1.length()-1;i>=0;i--){
    int a = s1[i] - '0';
    int b = s2[i] - '0';

    int sum = a+b + carry;

    ret = char('0' + sum%10) + ret;
    carry= sum/=10;
  }

  if(carry > 0)
    ret = char('0' + carry) + ret;

  return ret;
}


// '19' * 15

// 4

// 19 * 15
//. 
string mul(string s1, int num){
  int m = s1.length();
  string ret;

  vector<string> prods; // { "95", "190" }

  int cnt = 0;
  while(num > 0){ //1
    int multiplier = num%10;  // 4
    num/=10; // 0

    string buf; // ""
    int carry = 0; // 0
    for(int i=m-1;i>=0;i--){
      int n = s1[i] - '0'; // 6
      int product = n*multiplier; // 24
      int sum = product + carry; // 1 + 0 = 1
      buf = char(sum%10 +'0') + buf; // "19"
      sum/=10; // 0
      carry = sum; // 0
    }

    if(carry > 0)
      buf = char('0' + carry) + buf;

    for(int i=0;i<cnt;i++)
      buf+='0';

    prods.push_back(buf);
    cnt++;

  }

  ret = "0";
  for(string i:prods)
    ret = Add(ret, i); // 190 + "95"

  return ret;
}

 
// To execute C++, please define "int main()"
int main() {

  int n = 100;
  
  
  if(n == 0)
    cout<<"0";
  else if(n == 1)
    cout<<1;
  else{
    string ans = "1";
    for(int i=2;i<=n;i++){
      // cout<<i<<"\t"<<ans<<endl;
      // cout<<mul(ans,i)<<endl;
      ans = mul(ans,i);
    }
    
    cout<<ans;
  }
  
  return 0;
}


// Your previous Plain Text content is preserved below:

// This is just a simple shared plaintext pad, with no execution capabilities.

// When you know what language you'd like to use for your interview,
// simply choose it from the dots menu on the tab, or add a new language
// tab using the Languages button on the left.

// You can also change the default language your pads are created with
// in your account settings: https://app.coderpad.io/settings

// Enjoy your interview!