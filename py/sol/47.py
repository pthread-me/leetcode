#! /usr/bin/python3
#from typing import Self


# similar to permutations except now we use a set to decide if an element
# is to be swapped to the front
class Solution:
    def permuteUnique(self, nums: list[int]) -> list[list[int]]:
        res: list[list[int]] = []
        nums.sort()

        def per(i:int):
            print(nums[:i])
            if i==len(nums):
                res.append(nums[:])
            
            swapped: set[int] = set()
            for j in range(i, len(nums)):
                if nums[j] not in swapped:
                    swapped.add(nums[j])
                    nums[i], nums[j] = nums[j], nums[i]
                    per(i+1)
                    nums[i], nums[j] = nums[j], nums[i]

        per(0)
        return res

if __name__ == "__main__":
    s = Solution()
    l = [1,1,3]
    r = s.permuteUnique(l)
    print(r)

    
