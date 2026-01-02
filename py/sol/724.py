#! /usr/bin/python3
from include.leetcode_structs import *
from math import *

class Solution:
    def pivotIndex(self, nums: list[int]) -> int:
        if len(nums) == 1:
            return 0

        pref: list[int] = [0 for _ in range(len(nums)+1)]
        
        for i in range(1, len(pref)):
            pref[i] = pref[i-1] + nums[i-1]
        
        for i in range(0, len(pref)-1):
            if pref[i] == pref[-1] - pref[i+1]:
                return i

        return -1
if __name__ == "__main__":
    S= Solution()
    s = [1,7,3,6,5,6]
    r= S.pivotIndex(s)
    print(r)

