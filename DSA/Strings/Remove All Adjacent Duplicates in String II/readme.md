# Remove All Adjacent Duplicates in String II

[source](https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/)

You are given a string s and an integer k, a k duplicate removal consists of choosing k adjacent and equal letters from s and removing them, causing the left and the right side of the deleted substring to concatenate together.

We repeatedly make k duplicate removals on s until we no longer can.

Return the final string after all such duplicate removals have been made. It is guaranteed that the answer is unique.

**Example 1:**
```
Input: s = "abcd", k = 2
Output: "abcd"
Explanation: There's nothing to delete.
```

**Example 2:**

```
Input: s = "deeedbbcccbdaa", k = 3
Output: "aa"
Explanation: 
First delete "eee" and "ccc", get "ddbbbdaa"
Then delete "bbb", get "dddaa"
Finally delete "ddd", get "aa"
```

**Example 3:**

```
Input: s = "pbbcggttciiippooaais", k = 2
Output: "ps"
```

**Constraints:**


-    1 <= s.length <= 10<sup>5</sup>
-   2 <= k <= 10<sup>4</sup>
-    s only contains lower case English letters.

**Solution Approach**

[source](https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/discuss/392867/C%2B%2B-3-approaches)

**Approach 1: Brute-force**

Just keep removing duplicates until there is no more. When we find a duplicate, we call the same function recursively with that duplicate removed.

```cpp
string removeDuplicates(string s, int k) {
  for (auto i = 1, cnt = 1; i < s.size(); ++i) {
    if (s[i] != s[i - 1]) cnt = 1;
    else if (++cnt == k)
      return removeDuplicates(s.substr(0, i - k + 1) + s.substr(i + 1), k);
  }
  return s;
}
```

Or, we can do the same iteratively. It's a bit harder on eyes but easier on memory :)

```cpp
string removeDuplicates(string s, int k, bool replaced = true) {
  while (replaced) {
    replaced = false;
    for (auto i = 1, cnt = 1; i < s.size() && !replaced; ++i) {
      if (s[i] != s[i - 1]) cnt = 1;
      else if (++cnt == k) {
        s = s.substr(0, i - k + 1) + s.substr(i + 1);
        replaced = true;
      }
    }
  }
  return s;
}
```

Complexity Analysis

Time: O(n * n / k). We scan the entire string for each duplicte we find and remove.
Memory:

    O(n * n / k) for the recursive approach.
    O(1) for the iterative approach.


**Approach 2: Two pointers**

```cpp
string removeDuplicates(string s, int k) {
  auto j = 0;
  vector<int> cnt(s.size(), 1);
  for (auto i = 0; i < s.size(); ++i, ++j) {
    s[j] = s[i];
    if (j > 0 && s[j] == s[j - 1]) cnt[j] = cnt[j - 1] + 1;
    else cnt[j] = 1;
    if (cnt[j] == k) j -= k;
  }
  return s.substr(0, j);
}
```

Complexity Analysis

Time: O(n). We process each character in the input string once.
Memory: O(n) to track the running count for each character.


**Approach 3: Stack**

```cpp
string removeDuplicates(string s, int k) {
  vector<pair<char, short>> st;
  string res;
  for (auto ch : s) {
    if (st.empty() || st.back().first != ch) st.push_back({ ch, 0 });
    if (++st.back().second == k) st.pop_back();
  }
  for (auto& p : st) res += string(p.second, p.first);
  return res;
}
```

Complexity Analysis

Time: O(n). We process each character in the input string once.
Memory: O(n) for the stack.

Conclusion

A brute-force solution is accepted with the same runtime as other solutions. Unless this problem requires a limiar-time solution and has test cases to check it, I would consider it Easy, not Medium.