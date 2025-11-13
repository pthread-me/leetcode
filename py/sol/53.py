#! /usr/bin/python3
from include.leetcode_structs import *

# check the max subarray we can construct that ends at i
# if the max at i-1 is less than the value of i then we take it byitself else merge


class Solution:
    def maxSubArray(self, nums: list[int]) -> int:
        if len(nums) <2:
            return nums[0]

        dp: list[int] = [nums[0]] + ([0] * (len(nums)-1)) 
        m: int = nums[0]

        for i in range(1, len(nums)):
            if dp[i-1] < 0:
                dp[i] = nums[i]
            else:
                dp[i] = nums[i] + dp[i-1]
            
            if m<dp[i]:
                m = dp[i]

        return m
                          
if __name__ == "__main__":
    S= Solution()
    nums = [-2,1,-3,4,-1,2,1,-5,4]
    r= S.maxSubArray(nums)
    print(r)
