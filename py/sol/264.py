#! /usr/bin/python3
from typing import Self

# Check solution list on leetcode for explaination, i couldnt figure this one out myself

class Solution:
    def nthUglyNumber(self, n: int) -> int:
        dp: list[int] = [1] 
        i, j, k = 0, 0, 0

        for _ in range(n):
            cur: int = min(dp[i]*2, dp[j]*3, dp[k]*5)
            if cur == dp[i]*2:
                i+=1
            if cur == dp[j]*3:
                j+=1
            if cur == dp[k]*5:
                k+=1
            dp.append(cur)

        return dp[n-1]


        

              
if __name__ == "__main__":
    S = Solution()
    a = 10
    r = S.nthUglyNumber(a)
    print(r)

