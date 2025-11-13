#! /usr/bin/python3
from include.leetcode_structs import *


# start by sorting the intervals so that the first starts first
# for every remaining interval e, if the start of e <= the end of the last interval
# in the res we merge, else they are seperate so we just append e

# since we sorted them we know that every e' after e. e'[0] > e[0]
class Solution:
    def merge(self, intervals: list[list[int]]) -> list[list[int]]:
        intervals.sort()
        res: list[list[int]] = [intervals[0]]

        for i in range(1, len(intervals)):
            if intervals[i][0] <= res[-1][1]:
                res[-1][1] = max(intervals[i][1], res[-1][1])
            else:
                res.append(intervals[i])
        
        return res

if __name__ == "__main__":
    S= Solution()
    l = boxGrid = [[2,6],[1,3],[8,10],[15,18]]
    r = S.merge(l)
    print(r)
    
