#! /usr/bin/python3
import heapq

class Solution:
    def maxEvents(self, events: list[list[int]]) -> int:
        events.sort()
        minheap: list[int] = []

        day = 1
        attend = 0
        
        
        i = 0
        while i < len(events):
            e = events[i]
            for j in range(i, len(events)):
                if events[j][0] == day:
                    print(f"pushed: {events[j][1]}")
                    heapq.heappush(minheap, events[j][1])
                    i += 1
                else:
                    break
            
            while len(minheap)>0 and minheap[0] < day:
                print(f"expired: {minheap[0]}")
                _ = heapq.heappop(minheap)

            if len(minheap) > 0:
                print(f"attended: {minheap[0]}")
                _ = heapq.heappop(minheap)
                attend += 1
            
            day += 1
            

        while len(minheap) > 0:
            e = heapq.heappop(minheap)
            if e >= day:
                print(f"attended: {e}")
                attend += 1
                day += 1

        return attend

if __name__ == "__main__":    
    S = Solution()
    r = S.maxEvents([[1,5], [2,3],[2,3], [1,5], [1,5]])
    print(r)
