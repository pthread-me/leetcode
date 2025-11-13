#! /usr/bin/python3
#from typing import Self
        
        
class Solution:
    def permute(self, nums: list[int]) -> list[list[int]]:
        res: list[list[int]] = []

        def per(i:int):
            if i == len(nums):
                res.append(nums.copy())

            for j in range(i, len(nums)):
                nums[i], nums[j] = nums[j], nums[i]
                per(i+1)
                nums[i], nums[j] = nums[j], nums[i]
        
        per(0)
        return res

if __name__ == "__main__":
    s = Solution()
    l = [5,4,6]
    r = s.permute(l)
    print(r)

    
