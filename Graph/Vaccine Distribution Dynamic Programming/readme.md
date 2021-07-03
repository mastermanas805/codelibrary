# Vaccine distribution
There is a large manufacturer of vaccine which produces M types of vaccines (whose formulas are derived from different pharma brands). The manufacturer needs to divide all the vaccines between N dealers. It is acceptable if some dealers do not get any vaccine. However, no dealer wants vaccines of different kinds which means that all vaccines that a dealer gets need to be of the same type.
The manufacturer also knows that dealers will be jealous if a dealer gets too many vaccines. As an approximation, the jealousy level among the dealers is defined as the largest number of vaccines given to any dealer.

# Task

Help the manufacturer to divide all the vaccines among the dealers such that the jealousy level is minimized.

**Example**

**Assumptions**

-    N = 5
-    M= 2
-    arr= [7,4]

**Approach**

- There are 7 vaccines of 1st type and 4 vaccines of 2nd type. Let the two types be defined by P and Q.
- So if the manufacturer divides the vaccines as PP, PP, PPP, QQ, QQ. This will be optimal distribution.
- Thus, the answer is 3.

Function description

Complete the function solve provided in the editor. This function takes the following 3 parameters and returns the minimum possible jealousy level:

    N: Represents the number of dealers
    M: Represents the number of types of vaccines
    arr: Represents the array of M integers where arri represents the number of vaccines of type i

**Input format**

Note: This is the input format that you must use to provide custom input (available above the Compile and Test button).


- The first line contains T denoting the number of test cases. T also specifies the number of times you have to run the solve function on a different set of inputs.

- For each test case:
    -     The first line of input contains two positive integers N and M.
    -     The next line contains M space-separated positive integers, with the Kth integer denoting the number of vaccines of type K.

**Output format**

For each test case, print the minimum possible jealousy level in a new line.

**Constraints**
- 1 ≤ T ≤ 10 
- 1 ≤ N ≤ 10<sup>9</sup>
- 1 ≤ M ≤ 100000
- M ≤ N
- 1 ≤ arr[i] ≤ 10<sup>9</sup>

# Code snippets (also called starter code/boilerplate code)

This question has code snippets for C, CPP, Java, and Python.

**Sample input 1**
```

1

7 5

7 1 7 4 4

```

**Output**

```
4
```

**Explanation**

The first line contains the number of test cases, T = 1.

The first test case

Given

    N = 7
    M= 5
    arr= [7,1,7,4,4]

Approach

Following is the optimal distribution of vaccines:

    Dealer 1: 4 vaccines of type 1
    Dealer 2: 3 vaccines of type 1
    Dealer 3: 1 vaccine of type 2
    Dealer 4: 3 vaccines of type 3
    Dealer 5: 4 vaccines of type 3
    Dealer 6: 4 vaccines of type 4
    Dealer 7: 4 vaccines of type 5

Thus, the answer is 4.