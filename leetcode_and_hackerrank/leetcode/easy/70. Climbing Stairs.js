// You are climbing a staircase. It takes n steps to reach the top.
// Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

// Example 1:

// Input: n = 2
// Output: 2
// Explanation: There are two ways to climb to the top.
// 1. 1 step + 1 step
// 2. 2 steps
// Example 2:

// Input: n = 3
// Output: 3
// Explanation: There are three ways to climb to the top.
// 1. 1 step + 1 step + 1 step
// 2. 1 step + 2 steps
// 3. 2 steps + 1 step

/**
 * @param {number} n
 * @return {number}
 dp[current] được tính bằng cách cộng các cách để đạt được hai bước trước đó: dp[current-1] + dp[current-2]. Điều này dựa trên thực tế là ban có thể thực hiện 1 bước từ hiện tại-1 hoặc 2 bước từ hiện tại-2 để đạt được hiện tại
 */
 var climbStairs = function(n) {
    let dp = [0, 1, 2];
    let current = 3;
    while(current <= n) {
        dp[current] = dp[current-1] + dp[current-2];
        current++;
    }
    return dp[n];
 };