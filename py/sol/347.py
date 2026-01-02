#!/usr/bin/python3

import heapq

# My initial solution was a hashmap which works fine,

# we can use a maxheap, first use a hashmap to find the frequency of the elements
# then have a max_heap of pairs where we compare based on the freq
# python only has a min heap so a trick we can use is to negate the frequecy (times -1)
# if we were not dealing with ints/floats we would need to modify internal funcs or implement it ourselves. easy 
class Solution:
    def topKFrequent(self, nums: list[int], k: int) -> list[int]:
        h: dict[int, int] = {}

        for e in nums:
            if e in h.keys():
                h[e] += 1
            else:
                h[e] = 1
        
        queue = list(h.items())
        print(queue)
        queue = list(map(lambda x: (x[1]*-1, x[0]), queue))
        print(queue)
        
        max_heap = []
        for e in queue:
            heapq.heappush(max_heap, e)

        res = []
        for _ in range(0, k):
            res.append(heapq.heappop(max_heap)[1])
        return res
if __name__ == "__main__":
    s= Solution()
    r = s.topKFrequent([7,7,7,7,1,1,1,2,2,5], 2)
    print(r)
