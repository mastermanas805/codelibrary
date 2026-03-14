// https://leetcode.com/problems/new-21-game
// Difficulty: Medium

#include <bits/stdc++.h>
using namespace std;

double new21Game(int n, int k, int maxPts) {
    double p[n + 1], curr;
    p[0] = 1;
    curr = k > 0 ? 1 : 0;
    
    // Calculate the probabilities for each possible point value
    for (int i = 1; i <= n; i++) {
        p[i] = curr / maxPts;
        
        // If Alice's points are less than k, update curr with the new probability
        if (i < k)
            curr += p[i];
        
        // If Alice's points are more than maxPts, subtract the probability
        // of points she gained maxPts steps earlier
        if (i - maxPts >= 0 && i - maxPts < k)
            curr -= p[i - maxPts];
    }
    
    // Calculate the probability that Alice has n or fewer points by summing the probabilities
    // from k to n (inclusive)
    return accumulate(p + k, p + n + 1, 0.0);
}


// - `p[i]` represents the probability of Alice having `i` points at some point during the game.
// - `curr` is a cumulative value that keeps track of the probability of getting `k` or fewer points.
// - The loop iterates from `1` to `n` to calculate the probability of having `i` points.
// - The probability is calculated as `curr / maxPts` because Alice can draw any number between 1 and `maxPts`.
// - If Alice's current points are less than `k`, `curr` is updated with the new probability, as she can continue drawing.
// - If Alice's current points are greater than or equal to `maxPts`, the probability of points gained `maxPts` steps earlier is subtracted from `curr`, as this would cause her points to exceed `k`.

// Finally, the `accumulate` function sums up the probabilities from `k` to `n` inclusive, which represents the probability of Alice having `n` or fewer points.

// Time Complexity: O(n)
// Space Complexity: O(n)
