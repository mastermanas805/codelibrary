# Exp

p.s - https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/

src - https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/discuss/709227/JavaC%2B%2BPython-Two-Sum

## Intuition

Almost same as problem two sum.
If we want to know the count of subarray in sorted array A,
then it's exactly the same.
Make sure you can do two sum before continue.

## Explanation

Sort input A first,
For each A[i], find out the maximum A[j]
that A[i] + A[j] <= target.

For each elements in the subarray A[i+1] ~ A[j],
we can pick or not pick,
so there are 2 ^ (j - i) subsequences in total.
So we can update res = (res + 2 ^ (j - i)) % mod.

We don't care the original elements order,
we only want to know the count of sub sequence.
So we can sort the original A, and the result won't change.

## Complexity

Time O(NlogN)
Space O(1) for python
(O(N) space for java and c++ can be save anyway)
