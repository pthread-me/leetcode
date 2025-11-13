#! /usr/bin/python3
from include.leetcode_structs import *
import heapq


# n log(26) solution, should work but it gives TLE, you can do a sort and two finger but i wont for now
class Solution:
    def repeatLimitedString(self, s: str, repeatLimit: int) -> str:
        def key_to_char(a: int) -> str:
            return chr(-a)
        def char_to_key(c: str) -> int:
            return - ord(c)

        freq: dict[str, int] = {}
        max_heap: list[int] = []
        res: list[str] = []
            
        for e in s:
            if e not in freq:
                freq[e] = 1
                heapq.heappush(max_heap, char_to_key(e))
            else:
                freq[e] = freq[e] + 1

        while len(max_heap) > 1:
            c1: str = key_to_char(heapq.heappop(max_heap))                    
            c2: str = key_to_char(heapq.heappop(max_heap))

            res = res + [c1] * (min(freq[c1], repeatLimit))
            freq[c1] -= min(freq[c1], repeatLimit)

            if freq[c1] > 0:
                res = res + [c2] 
                freq[c2] -= 1
                heapq.heappush(max_heap, char_to_key(c1))

                if freq[c2] > 0:
                    heapq.heappush(max_heap, char_to_key(c2))
            else:
                heapq.heappush(max_heap, char_to_key(c2))



        if len(max_heap) > 0:
            c: str = key_to_char(heapq.heappop(max_heap))                    
            count: int = 0
            if len(res) > 0 and res[-1] == c:
                for e in res[::-1]:
                    if e == c:
                        count += 1
                    else:
                        break
            else:
                count = min(freq[c], repeatLimit)

            res = res + [c] * count

        return "".join(res)




if __name__ == "__main__":
    S= Solution()
    s = "cczazcc"
    repeatLimit = 3
    r = S.repeatLimitedString(s, repeatLimit)
    print(r)
    
