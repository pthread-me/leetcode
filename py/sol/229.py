#! /usr/bin/python3
from typing import Self

# We use the boyer moore algorithm for majority:
#
# The idea is to extract as many triplets with distrinct elements as possible
# once no more distinct triplets can be extracted this means there exists at most
# 2 elements that have a count > n/3
class Solution:
   def majorityElement(self, nums: list[int]) -> list[int]:
        e1: int = 0
        v1: int = 0

        e2: int  = 0
        v2: int = 0

        for e in nums:
            if e == e1:
                v1 +=1
            elif e == e2:
                v2 += 1
            elif v1 == 0:
                e1 = e
                v1 = 1
            elif v2 == 0:
                e2 = e
                v2 = 1
            else:
                v1 -=1
                v2 -=1



        threshold = len(nums) // 3
        c1: int = 0
        c2: int = 0
        res: list[int] = []

        for e in nums:
            if e == e1:
                c1 += 1
            elif e == e2:
                c2 +=1
        
        if c1>threshold:
            res.append(e1)
        if c2>threshold:
            res.append(e2)

        return res






if __name__ == "__main__":
    S= Solution()
    l = [4,1,2,3,4,4,3,2,1,4]
    r = S.majorityElement(l)
    print(r)
