#! /usr/bin/python3
#from typing import Self
class Solution:
    def removeCoveredIntervals(self, intervals: list[list[int]]) -> int:
        intervals.sort() 
        i: int = 0
        j: int = 1
        count: int = 0

        while j<len(intervals):
            if intervals[i][0] == intervals[j][0]:
                i+=1
                j+=1
                count +=1
            elif intervals[i][1] >= intervals[j][1]:
                j+=1
                count +=1
            else:
                i = j
                j+=1

        return len(intervals) - count



if __name__ == "__main__":
    s = Solution()
    l = [[1,4],[2,3]] 
    r = s.removeCoveredIntervals(l)
    print(r)
