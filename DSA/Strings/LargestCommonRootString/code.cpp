// Given 2 strings S1 and S2 . Find largest string S3 such that S1 and S2 both are concatenation of S3 string
// example:- S1: abaaba S2: abaabaaba then S3 :- aba

#include <iostream>
#include <string>

using namespace std;

string smallestConcatenation(string s1) {
    int n = s1.length();
    for (int i = 1; i <= n/2; i++) {
        if (n % i == 0) {
            string s2 = s1.substr(0, i);
            int j = i;
            while (j < n && s1.substr(j, i) == s2) {
                j += i;
            }
            if (j == n) {
                return s2;
            }
        }
    }
    return "";
}

int main() {
    string s1 = "abaabaaba";
    string s2 = "abaaba";

    string x = smallestConcatenation(s1), y = smallestConcatenation(s2);

    if (x == y) {
        cout << "S3: " << x << endl;
    } else {
        cout << "No such string exists" << endl;
    }
    return 0;
}
