
Given an array of distinct positive integers representing coin denominations and a single non-negative integer n representing a target amount of money, write a function that returns the number of ways to make change for that target amount using the given coin denominations.

Note that an unlimited amount of coins is at your disposal.
Sample Input

n = 6
denoms = [1, 5]

Sample Output

2 // 1x1 + 1x5 and 6x1


Test Case 1

{
  "n": 6,
  "denoms": [1, 5]
}

Test Case 2

{
  "n": 0,
  "denoms": [2, 3, 4, 7]
}

Test Case 3

{
  "n": 9,
  "denoms": [5]
}

Test Case 4

{
  "n": 7,
  "denoms": [2, 4]
}

Test Case 5

{
  "n": 4,
  "denoms": [1, 5, 10, 25]
}

Test Case 6

{
  "n": 5,
  "denoms": [1, 5, 10, 25]
}

Test Case 7

{
  "n": 10,
  "denoms": [1, 5, 10, 25]
}

Test Case 8

{
  "n": 25,
  "denoms": [1, 5, 10, 25]
}

Test Case 9

{
  "n": 12,
  "denoms": [2, 3, 7]
}

Test Case 10

{
  "n": 7,
  "denoms": [2, 3, 4, 7]
}