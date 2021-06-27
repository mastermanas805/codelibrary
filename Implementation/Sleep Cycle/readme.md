# Sleep Cycle
[source](https://www.codechef.com/START5C/problems/SLPCYCLE)

Chef has been studying the human sleep cycle for years. He divides a day into L units of time (numbered 1 through L). Chef's research shows that his body requires spending only H

continuous units of time per day on sleep — then, he can stay active during work. However, in case of travel or any other responsibilities, he might not be able to achieve this ideal state.

Next, Chef noticed that if he sleeps for x
(x<H) continuous units of time and then performs some other activity, he can still meet his daily sleep quota, but the remaining time he needs to spend on continuously sleeping becomes 2⋅(H−x). He can further split this sleeping time in the same way, i.e. if he now sleeps for y more (y<2⋅(H−x)) continuous units of time, his required sleeping time becomes 2⋅(2⋅(H−x)−y), and so on.

You are given a string S with length L; for each valid i, the i-th character of this string is '0' if the i-th unit of time is free (so Chef can use it to sleep) or '1' if it is occupied.

Can Chef ever get enough sleep to feel fresh during his work, given that he can choose when to sleep in his free time?

## Input

- The first line of the input contains a single integer T denoting the number of test cases. The description of T test cases follows.

- The first line of each test case contains two space-separated integers L and H

- The second line contains a single string S with length L

## Output

Print a single line containing the string "YES" if Chef can have the required amount of sleep or "NO" if he cannot (without quotes).

You may print each character of each string in uppercase or lowercase (for example, the strings "yEs", "yes", "Yes" and "YES" will all be treated as identical).

## Constraints

- 1≤T≤10
- 1≤H≤L≤10<sup>5</sup>
- S contains only characters '0' and '1'

## Example Input
```
4
3 1
111
3 1
101
7 5
0000100
6 5
000010
```

## Example Output
```
NO
YES
YES
NO
```

## Explanation

**Example case 1:**

 Chef needs only 1 unit of sleep, but since he is busy all the time, he cannot sleep at all.


**Example case 2:**

Chef needs only 1 unit of sleep and he has exactly one unit of time when he is free, so he can sleep during that unit of time.


**Example case 3:**

Chef needs 5 continuous units of sleep. First, he spends the first 4 free units of time, and then he needs 2⋅(5−4)=2 continuous units of sleep, which he has available as the last 2 free units of time.

**Example case 4:**

Chef needs 5 units of sleep. If he spends the first 4 units of time, he still needs 2⋅(5−4)=2 continuous units of sleep, but only a single unit of time is left now, so he is unable to get enough sleep.


## EXPLANATION

As we know that if we sleep x(<H)x(<H)x(<H) units then we need to sleep 2∗(H−x)2*(H-x)2∗(H−x) units more next time.

So when we have some x(<H)x(<H)x(<H) units of free time available then should us sleep or not?
We should sleep only if, it reduces our remaining sleep units that is we should sleep xxx units only if 

```math
2∗(H−x)<H.
=>2∗H−2∗x<H
=> 2*H - 2*x < H
=>2∗H−2∗x<H
=>2∗H−H<2∗x
=> 2*H - H < 2*x
=>2∗H−H<2∗x
=>H<2∗x
=> H < 2*x
=>H<2∗x
=>x>H/2
=> x > H/2
=>x>H/2
```

So iterate over the given string SSS, find countcountcount of continuous 0s0s0s, check if count>H/2, if yes then sleep for this time and update the HHH as following: H=2∗(H−count)

If at any point we have H<=0H <= 0H<=0 then we are able to achieve the requirement otherwise no.
TIME COMPLEXITY:

O(L) per test case