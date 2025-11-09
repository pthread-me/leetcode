#! /usr/bin/python3
from include.leetcode_structs import *

# dp[i] = min(dp[i-1+1, dp[i-2]+4, dp[i-3]+9]) + cost[i]
# we just save results from 0 to n the extract dp[n]

class Solution:
    def climbStairs(self, n: int, costs: list[int]) -> int:
        costs = [0] + costs
        jump = [1,4,9]
        dp: list[int] = [0] * (n+1)

        for i in range(1, len(dp)):
            pos: list[int] = [dp[i-j] + jump[j-1] for j in range(1, 4) if i-j>=0]
            dp[i] = min(pos) + costs[i]

        return dp[-1]
            
            



if __name__ == "__main__":
    S= Solution()
    n = 4
    costs = [5,1,6,2]
    r = S.climbStairs(n, costs)
    print(r)
    
