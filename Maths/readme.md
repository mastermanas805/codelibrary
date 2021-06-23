# Binary String on Steroids
[source](https://www.codechef.com/problems/BNSONSTR)
A circular binary string is called good if it contains at least one character '1' and there is an integer d such that for each character '1', the distance to the nearest character '1' clockwise is d

You are given a circular binary string S
with length N. You may choose some characters in this string and flip them (i.e. change '1' to '0' or vice versa). Convert the given string into a good string by flipping the smallest possible number of characters.

# Input
- The first line of the input contains a single integer T denoting the number of test cases. The description of T test cases follows.
- The first line of each test case contains a single integer N
- The second line contains a single string S with length N.

# Output

Print a single line containing one integer ― the minimum number of flips required to transform the initial string into a good string.

# Constraints

- 1≤T≤100
- 1≤N≤5⋅10<sup>5</sup>
- S contains only characters '0' and '1'
- the sum of N over all test cases does not exceed 5⋅10<sup>5</sup>

# Example Input

```
2
6
110011
4
0001
```

# Example Output
```
2
0
```

# Approach

## QUICK EXPLANATION

    The distance between '1’s can only be a factor of NNN.Try all factors of NNN as distance.
    For each factor, try all possible start points. i.e. For distance ddd, there are ddd positions where ‘1’ should appear, and the rest string should be filled with zeros.
    Find minimum Hamming distance of given string to any of the valid strings found above.

## EXPLANATION
### Valid distance between '1’s

Let’s define the distance between two positiions iii and jjj in 000-based indexing as j−ij-ij−i if i≤ji \leq ji≤j and j+N−ij+N-ij+N−i otherwise. Denoting distance by d(i,j)d(i, j)d(i,j).

Let’s suppose, we have a good string with kkk occurrences of 1s, and the distance between each ‘1’ from the next one is ddd. Assuming the positions of ones are p1,p2…pkp_1, p_2 \ldots p_kp1​,p2​…pk​, we have d(pi,pi+1)=dd(p_i, p_{i+1}) = dd(pi​,pi+1​)=d for all 1≤i<k1 \leq i < k1≤i<k and d(pk,p1)=dd(p_k, p_1) = dd(pk​,p1​)=d as well.

We can see that starting from p1p_1p1​, moving to next pip_ipi​ until reaching p1p_1p1​ again, leads to visiting NNN positions exactly once. So, we can claim that d∗k=Nd*k = Nd∗k=N holds.

Claim: If a circular string of length NNN is good, then the distance between each ‘1’ and the next ‘1’ is a factor of NNN.

Hence, let us try all divisors ddd one by one, and compute the minimum number of operations needed to convert sss into a good string with distance ddd between ones.

### All good string s with distance d

Let’s suppose we fix the distance between each ‘1’ and the next as ddd where ddd is a factor of NNN.
The circular binary string would look like ‘1’ followed by d−1d-1d−1 ‘0’, then ‘1’ followed by d−1d-1d−1 '0’s and so on, covering the whole string. For N=6,d=3N = 6, d = 3N=6,d=3, we get string 100100.

But there are string 010010 and string 001001 as well with d=3d = 3d=3.

We need to fix the position of the first occurrence fff of ‘1’ in the string, as the first occurrence, as fff and ddd defines the whole good circular string uniquely.

Pair (f,d)(f, d)(f,d) represent a string with each ‘1’ having distance ddd from the next one, and position fff contains ‘1’. We can see that for each position ppp, it contains ‘1’ if and only if p mod d=fp \bmod d = fpmodd=f, and ‘0’ otherwise.

### Computing minimum Hamming distance to good string

Let’s try pair (f,d)(f, d)(f,d), representing string TTT, and try to compute its hamming distance from given string sss. We know that TTT contains exactly N/dN/dN/d ones, and the rest zeros, so let’s iterate on those positions. Let’s make a set AAA denoting the set of positions of '1’s in TTT.

We need to count the number of positions ppp in set AAA such that sps_psp​ = ‘0’, and number of positions not in AAA such that sps_psp​ = ‘1’, as the sum of these values would be the hamming distance.

Let c denote the number of ones in whole string sss, and xxx denote the number of ones in positions in set ppp present in set AAA such that sps_psp​ = ‘1’. We can see that The hamming distance is (N/d−x)+(c−x)  ⟹  N/d+c−2∗x(N/d - x) + (c-x) \implies N/d + c - 2*x(N/d−x)+(c−x)⟹N/d+c−2∗x.

N/d−xN/d -xN/d−x is the number of positions where T contains ‘1’, but sss contains ‘0’, and (c−x)(c-x)(c−x) denote the number of positions where T contains ‘0’ but sss contains ‘1’

We can compute ccc beforehand, and compute xxx, the number of ones at positions ppp such that p mod d=fp \bmod d = fpmodd=f, in time O(N/d)O(N/d)O(N/d) time by following loop.

x = 0
for(int p = f; p < N; p += d)
    if(s[p] == '1')
        x++

Hence, we shall try all valid pairs (f,d)(f, d)(f,d) one by one, compute Hamming distance from string sss, and print minimum.
Time complexity analysis

For a fixed distance ddd, let’s consider all start points fff. There are exactly ddd unique choices for fff, and computing each one takes N/dN/dN/d iterations, leading to total NNN iterations.

Hence, for each factor ddd of NNN, we need O(N)O(N)O(N) time, leading to time complexity O(N∗σ(N))O(N*\sigma(N))O(N∗σ(N)), where σ(N)\sigma(N)σ(N) is the divisor function.
TIME COMPLEXITY

The time complexity is O(N∗σ(N))O(N*\sigma(N))O(N∗σ(N)) per test case.
