#! /usr/bin/python3
from include.leetcode_structs import *

# This is a double knapsack problem, so a dp table where we iterate from m..0 as to 
# not double count elements
# for each s we check if adding s improves the current bound, if so we add it else not
# to ensure the bound we only iterate till i>=zeros and j>=ones (zeros is the number of 0 in s) so we dont check negative values
class Solution:
    def findMaxForm(self, strs: list[str], m: int, n: int) -> int:
        dp: list[list[int]] = [[0 for _ in range(n+1)] for _ in range(m+1)]

        for s in strs:
           zeros  = len(s.replace("1", "")) 
           ones = len(s.replace("0", "")) 

           for i in range(m, zeros-1, -1):
               for j in range(n, ones-1, -1):
                   dp[i][j] = max(dp[i][j], dp[i-zeros][j-ones]+1)

        
        return dp[m][n]
        
if __name__ == "__main__":
    S= Solution()
    strs = ["10","0001","111001","1","0"]
    m = 5
    n = 3
    r= S.findMaxForm(strs, m,n)
