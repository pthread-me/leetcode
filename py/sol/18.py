#! /usr/bin/python3
from include.leetcode_structs import *

# fix two pointers and run 2 sum, n for 2 sum and n^2 for the fixed pointers

class Solution:
    def fourSum(self, nums: list[int], target: int) -> list[list[int]]:
        nums.sort()
        res: list[list[int]] = []
        
        for i in range(0, len(nums)-3):
            if 0<i and nums[i] == nums[i-1]: continue

            for j in range(len(nums)-1, i+2, -1):
                if j<len(nums)-1 and nums[j] == nums[j+1]: continue

                l = i+1
                r = j-1
                while l<r:
                    s = nums[i]+ nums[j] + nums[r] + nums[l]
                    if s == target:
                        res.append([nums[i], nums[l], nums[r], nums[j]])
                        while l<r and nums[l] == nums[l+1]: l+=1
                        while l<r and nums[r] == nums[r-1]: r-=1
                        l+=1
                        r-=1
                    elif s<target:
                        l+=1
                    else:
                        r-=1
        return res



if __name__ == "__main__":
    S= Solution()
    nums = [2,2,2,2,2]
    target = 8
    r= S.fourSum(nums, target)
    print(r)
