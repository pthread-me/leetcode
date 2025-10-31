#! /usr/bin/python3
from typing import Self

# We start by removing nonpositive numbers and duplicates
# find the minimum value m, which we also set as the offset
# We now treat the array as a hash map, swapping each element to a relative position
# where the index is the value - offset (if OB we skip)
# this leaves us with an array which should have the minimum value at index 0
# if minimum +1 exists then it would be at index 1 and so on
# we iterate over the array until nums[i] +1 != nums[i+1]. in that case nums[i]+1 is the minimum
# value not in the array

class Solution:
    def firstMissingPositive(self, input: list[int]) -> int:
        nums:list[int] = [e for e in input if e > 0]
        nums = list(set(nums))

        if len(nums)==0:
            return 1
        m = min(nums)
        offset = m
        print(m) 
        
        i = 0
        while i< len(nums):
            new_pos = nums[i] - offset
            if new_pos == i or new_pos >= len(nums):
                i+=1
            else:
                temp = nums[new_pos]
                nums[new_pos] = nums[i]
                nums[i] = temp

        print(nums)
        if nums[0] > 1:
            return 1

        for i in range(1, len(nums)):
            if nums[i-1] == nums[i]-1:
                continue
            else:
                return i+1
        return nums[-1] + 1

if __name__ == "__main__":
    s = Solution()
    l = [7,8,2,9,1,11]
    r = s.firstMissingPositive(l)
    print(r)
