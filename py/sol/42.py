#! /usr/bin/python3
#from typing import Self

# We first handle duplicates
# check which half of the array is sorted
# we use that half to check if target is in it, if so we'd go to it else go to the other half

class Solution:
    def search(self, nums: list[int], target: int) -> bool:
        if len(nums) <2:
            return target in nums
        i: int = 0
        j: int = len(nums)-1

        while i<=j:
            m:int  = i+ (j-i)//2
            print(m)
            if nums[m] == target:
                return True
            
            # handle duplicates
            if nums[i] == nums[m] and nums[m] == nums[j]:
                i+=1
                j-=1
            elif nums[i] <= nums[m]:
                if nums[i] <= target < nums[m]:
                    j = m-1
                else:
                    i = m+1
            else:
                if nums[m] < target <= nums[j]:
                    i = m+1
                else:
                    j = m-1
        return False

if __name__ == "__main__":
    s = Solution()
    l = [1,1,1,1,1,1,1,1,1,13,1,1,1,1,1,1,1,1,1,1,1,1] 
    r = s.search(l, 13)
    print(r)
