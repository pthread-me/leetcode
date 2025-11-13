#! /usr/bin/python3
from include.leetcode_structs import *
# IMPORTANT

# first we reduce the problem to subset sum:
#   let P be the set of positives in nums and N the negatives
#   then the target t = sum(P) + sum(N)
#   if instead we *add* all the negatives (that is treat them as positives) we have it that
#   sum(P) + sum(-N) = sum(P) - sum(N) = S, where S is the total sum of nums

# adding the two equations we get:
#   2P = t+S -> P = (t+S)/2. 
#   so a solution only exists if t+S is even, then we only need to find the number of ways we can get sum(P) from nums
#   since that implicitly leaves the remaining elemns as negatives without changing the number of ways

# Look to the file named subset sum on how to do that

class Solution:
    def findTargetSumWays(self, nums: list[int], target: int) -> int:
        if target + sum(nums) %2 == 1:
            return 0
        else:
            nP:int = (target+sum(nums))//2

        dp: list[int] = [1] + [0 for _ in range(nP)]

        for e in nums:
            for j in range(nP, e-1, -1):
                dp[j] += dp[j-e]

        return dp[-1] 
if __name__ == "__main__":
    S= Solution()
    nums = [1,1,1,2]
    target = 3
    r= S.findTargetSumWays(nums, target)
    print(r)

