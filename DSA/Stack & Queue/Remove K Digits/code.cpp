// https://leetcode.com/problems/remove-k-digits/description/

class Solution {
public:
    string removeKdigits(string num, int k) {
        // If the number of digits to remove is the same as the length of the number, return "0".
        if (k == num.length()) {
            return "0";
        }

        // We add an extra '0' at the end to simplify the termination condition inside the loop.
        num += "0";

        stack<char> st; // Stack to store digits while considering removals.
        for (auto i : num) {
            // While the stack is not empty, the top digit is greater than the current digit 'i',
            // and we still have removals 'k' left, pop the stack and decrease 'k'.
            while (!st.empty() && st.top() > i && k > 0) {
                st.pop();
                k--;
            }
            st.push(i); // Push the current digit onto the stack.
        }

        string s, ret; // 's' for reversed number, 'ret' for the final result.
        while (!st.empty()) {
            s = st.top() + s; // Reconstruct the number in reverse order.
            st.pop();
        }

        int i = 0;
        // Find the index 'i' where the non-zero digits start.
        while (s[i] == '0')
            i++;

        // Build the final result by appending non-zero digits from 's' to 'ret'.
        while (i < s.length() - 1) {
            ret += s[i];
            i++;
        }

        // Return the final result, if not empty, else return "0".
        return ret != "" ? ret : "0";
    }
};
