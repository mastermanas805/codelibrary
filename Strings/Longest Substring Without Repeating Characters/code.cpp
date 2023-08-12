// https://leetcode.com/problems/longest-substring-without-repeating-characters
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.length();
        int maxLength = 0;
        int left = 0;
        vector<int> lastIndex(256, -1); // Store the last index of each character

        for (int right = 0; right < n; right++) {
            if (lastIndex[s[right]] != -1) {
                left = max(left, lastIndex[s[right]] + 1); // Move the left pointer to the next position after the repeated character
            }
            maxLength = max(maxLength, right - left + 1);
            lastIndex[s[right]] = right;
        }

        return maxLength;
    }
};
