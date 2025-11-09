#! /usr/bin/python3
#from typing import Self

class Solution:
    def removeDuplicates(self, nums: list[int]) -> int:
        if len(nums) < 3:
            return len(nums)

        j: int = 2

        for i in range(2, len(nums)):
            if nums[i] != nums[j-2]:
                nums[j] = nums[i]
                j+=1
        
        print(nums)
        return j


if __name__ == "__main__":
    s = Solution()
    l = [0,0,1,1,1,1,2,3,3]   
    r = s.removeDuplicates(l)
