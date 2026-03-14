# D2C Recuitables Sample Questions
## Problem Statement

An e-commerce site is planning to launch a game. In the game, you will be given a string initially and some Q queries, for each query you will have 2 integers L and R. For each query, you have to perform the following operations:

Arrange the letters from  L to R inclusive to make a Palindrome. If you can form many such palindromes, then take the one that is lexicographically minimum. Ignore the query if no palindrome is possible on rearranging the letters.

You have to find the final string after all the queries.

## Constraints:

- 1 <= Length(S) <= 10^5

- 1 <=  Q <= 10^5 

- 1<= L <= R <= Length(S)

## Input Format

First-line consists of the length of string S, 

Second-line contains the string S itself and the number Q separated by space.

The next Q lines consist of two integers L and R separated by space.

## Output Format

Print the string formed after all the operations.

## Sample Testcase #0

**Testcase Input**

```
4
mmcs 1
1 3
```

**Testcase Output**
```
mcms

```

## Explanation

The initial string is mmcs, there is 1 query which asks to make a palindrome from 1 3, so the palindrome will be mcm. Therefore the string will mcms.