// https://leetcode.com/problems/water-and-jug-problem

// You are given two jugs with capacities jug1Capacity and jug2Capacity liters. There is an infinite amount of water supply available. Determine whether it is possible to measure exactly targetCapacity liters using these two jugs.

// If targetCapacity liters of water are measurable, you must have targetCapacity liters of water contained within one or both buckets by the end.

// Operations allowed:

//     Fill any of the jugs with water.
//     Empty any of the jugs.
//     Pour water from one jug into another till the other jug is completely full, or the first jug itself is empty.

// Example 1:

// Input: jug1Capacity = 3, jug2Capacity = 5, targetCapacity = 4
// Output: true
// Explanation: The famous Die Hard example

// Example 2:

// Input: jug1Capacity = 2, jug2Capacity = 6, targetCapacity = 5
// Output: false

// Example 3:

// Input: jug1Capacity = 1, jug2Capacity = 2, targetCapacity = 3
// Output: true

#include <bits/stdc++.h>

class Solution
{
public:
    // Recursive function to calculate the greatest common divisor (GCD) of two numbers
    int gcd(int a, int b)
    {
        // GCD of a number and 0 is the number itself
        if (a == 0)
            return b;
        if (b == 0)
            return a;

        // Base case: if both numbers are equal, GCD is found
        if (a == b)
            return a;

        // If 'a' is greater than 'b', recursively calculate GCD of (a - b) and 'b'
        if (a > b)
            return gcd(a - b, b);
        
        // If 'b' is greater than 'a', recursively calculate GCD of 'a' and (b - a)
        return gcd(a, b - a);
    }
    
    // Function to check if it is possible to measure 'target' liters using jugs of capacities 'a' and 'b'
    bool canMeasureWater(int a, int b, int target)
    {
        // If the sum of the jug capacities is less than the target, it's not possible to measure the target amount
        if (a + b < target)
            return false;
        
        // If the target amount is a multiple of the GCD of the jug capacities, it's possible to measure the target amount
        if (target % gcd(a, b) == 0)
            return true;

        // Otherwise, it's not possible to measure the target amount using the given jugs
        return false;
    }
};
