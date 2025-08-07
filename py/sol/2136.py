#! /usr/bin/python3


# The question requires a greedy approach:
# First observe that the time required is the sum of all plant times + the max (of
#   all the grow times + the time started growing)
#
# the first is constant, to reduce the second: assume we have two time G1 and G2 such that:
# G1>=G2. If we growing of G1 starts at i and G2 at i+1 the end time (i, i+1)<=(i+1, i).
# That is it is always benificial for the plant with more grow time to start growing first.

# Thus we sort plants in decesnding grow time, then plant them

class Solution:
    def earliestFullBloom(self, plantTime: list[int], growTime: list[int]) -> int:
        seeds: list[tuple[int, int]] = [(growTime[i], plantTime[i]) for i in range(0, len(plantTime))]
        seeds = sorted(seeds)[::-1]
        
        last_day = 0
        cur_day = 0
        print(seeds)
        for e in seeds:
            print(cur_day, cur_day+e[1]-1, cur_day+e[0]+e[1])
            last_day = max(last_day, cur_day+e[0]+e[1])

            cur_day = cur_day+e[1]
            
        return last_day


if __name__ == "__main__":
    s = Solution()
    r = s.earliestFullBloom([1], [1])
    print(r)
