#! /usr/bin/python3
from typing import Self

class Solution:
    def containsNearbyDuplicate(self, nums: list[int], k: int) -> bool:
        map: dict[int, int] = {}

        for i,e in enumerate(nums):
            if e in map:
                if abs(i-map[e]) <= k:
                    return True
            
            map[e] = i


        return False
         

if __name__ == "__main__":
    S= Solution()
    l = [1,2,3,1,2,3]
    r = S.containsNearbyDuplicate(l, 2)
    print(r)
