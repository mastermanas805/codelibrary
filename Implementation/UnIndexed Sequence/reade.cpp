Avi likes integer sequences. His parents gave him a birthday gift that is an integer sequence of length n containing integers from 1 to n.

Let’s denote the sequence by p1, p2, p3, .. pn, where p1, p2, ...pn consist of 1, 2, 3, 4, ... n in any order.

Now Avi does not like a sequence if for any index in the sequence the index and the value at the index in sequence are equal, that is pi = i.

He wants to form a new sequence that satisfies the property that for any index i, pi != i, using the following operation minimum number of times.

Operation: Swap two adjacent elements in the sequence.

## Constraints

1 <= n <= 100000

1 <= pi <= n

## Input Format

The first contains an integer n.

The second line contains n integers, from 1 to n in any order. 

## Output Format

The output should contain one line denoting the minimum required number of operations to achieve this.

## Sample Testcase #0

**Testcase Input**
```
3
2 1 3
```

## Testcase Output
```
1
```

## Explanation

If we swap 1 and 3 in the array that is the index 1 and 2(0 - based), then we will receive the required format such that for any i, pi != i.