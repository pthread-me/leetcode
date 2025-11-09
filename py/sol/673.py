#! /usr/bin/python3
from include.leetcode_structs import *

# We keep track of 2 lists, l[i] the len of the longest seq ending at i
# and c[i] the number of such longest seq

# for every j < i where nums[j] < nums[i] we can extend something so:
# given that nums[i] > nums[j]
# if l[i] < l[j]+1 this means that we can form a new longest chain by extending substrings ending at j with nums[i]
# this increases len but not count

# on the other hand if l[i] == l[j] +1
# this means that there is some seperate chain before that can be extended by nums[j] but doesnt change the len
# so we increase the count by the number of those chains

# finally return the number of chains with max len

class Solution:
    def findNumberOfLIS(self, nums: list[int]) -> int:
        l: list[int] = [1] * len(nums)
        c: list[int] = [1] * len(nums)

        for i in range(0, len(nums)):
            for j in range(0, i):
                if nums[i] > nums[j]:
                    if l[i] == l[j] + 1:
                        c[i] += c[j]
                    elif l[i] < l[j]+1:
                        l[i] = l[j]+1
                        c[i] = c[j]

        max_len = max(l)
        res = 0

        for i in range(0, len(nums)):
            if l[i] == max_len:
                res += c[i]
        
        print(l , c)
        return res
        


if __name__ == "__main__":
    S= Solution()
    l = [1,2]
    r = S.findNumberOfLIS(l)
    print(r)
    
