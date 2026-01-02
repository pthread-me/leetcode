#! /usr/bin/python3

# We start by finding the groups of ranges that must be together,
# then it turns into a question of given n groups how many different combinations can we get
# so if n=2 we have 1,2,(1,2),(2,1)
class Solution:
    def countWays(self, ranges: list[list[int]]) -> int:
        ranges.sort()
        modulo: int = 10**9 + 7
        res: list[list[int]] = [ranges[0]]

        for e in ranges[1:]:
            if e[0] <= res[-1][1]:
                res[-1][1] = max(e[1], res[-1][1])
            else:
                res += [e]
        
        n: int = len(res)
         
        return 2**n % modulo

if __name__ == "__main__":
    S = Solution()
    ranges = [[6,10],[5,15]]
    r = S.countWays(ranges)
    print(r)
     
