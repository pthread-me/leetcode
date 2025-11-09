#! /usr/bin/python3
from include.leetcode_structs import *



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
    
