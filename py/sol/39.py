#! /usr/bin/python3
from include.leetcode_structs import *


class Solution:
    def combinationSum(self, candidates: list[int], target: int) -> list[list[int]]:
        res: list[list[int]] = []

        def rec(i:int, comb:list[int], cum: int):
            if cum == target:
                res.append(comb[:])
                return
            if i>= len(candidates):
                return

            if cum+candidates[i] <= target:
                comb.append(candidates[i])
                rec(i, comb, cum+candidates[i])
                _ = comb.pop()

            rec(i+1, comb, cum)

        rec(0, [], 0)
        return res

        
               
if __name__ == "__main__":
    S= Solution()
    nums = [2,3,5]
    target = 4
    r= S.combinationSum(nums, target)
    print(r)

