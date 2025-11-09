#! /usr/bin/python3
from include.leetcode_structs import *

class Solution:
    def numDecodings(self, s: str) -> int:
        if len(s) == 0 or s[0] == "0":
            return 0

        dp: list[int] = [0] * (len(s)+1)
        dp[0] = dp[1] = 1

        for i in range(2, len(dp)):
            if int(s[i-1]) > 0: 
                dp[i] += dp[i-1]
            if 10<= int(s[i-2:i])<=26: 
                dp[i] += dp[i-2]
        
        return dp[-1]
if __name__ == "__main__":
    S= Solution()
    l = "112"
    r = S.numDecodings(l)
    print(r)
    
