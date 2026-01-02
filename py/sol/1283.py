#! /usr/bin/python3
from math import ceil 

# We binary search over all possible solutions
class Solution:
    def smallestDivisor(self, nums: list[int], threshold: int) -> int:
        def acc(d: int)->bool:
            return sum((e-1)//d + 1 for e in nums) <= threshold 

        l: int = 1
        r: int = max(nums)
        
        while l<r:
            m = l+(r-l)//2

            if acc(m):
                r = m
            else:
                l = m+1

        return l
        

if __name__ == "__main__":
    S = Solution()

    nums = [21212,10101,12121]
    threshold = 1000000
    r = S.smallestDivisor(nums, threshold)
    print(r)

     
