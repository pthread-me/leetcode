#! /usr/bin/python3
from include.leetcode_structs import *

class Solution:
    def removeElement(self, nums: list[int], val: int) -> int:
        swap_pos = len(nums)-1

        for i in range(len(nums)-1, -1, -1):
            if nums[i] == val:
                print(f"swap {i, swap_pos}")
                nums[i], nums[swap_pos] = nums[swap_pos], nums[i]
                swap_pos -=1
    
        return swap_pos+1

if __name__ == "__main__":
    S= Solution()
    nums = [3,2,2,3, 2, 3]
    val = 3
    r= S.removeElement(nums, val)
    print(r)
