#! /usr/bin/python3

import math

# binary search of the range of possible values [i, j]
# if a value k is valid we set it as the answer and try a lower value,
# else try a higher value

class Solution:
    def minEatingSpeed(self, piles: list[int], h: int) -> int:
        i = 1
        j = max(piles)
        
        ans= j
        while i<=j:
            k = i+(j-i)//2
            rounds = sum([math.ceil(e/k) for e in piles])
            if rounds <=h :
                j = k-1
                ans = k
            else:
                i = k+1

        return ans
                
    
        
if __name__ == "__main__":    
    S = Solution()
    r = S.minEatingSpeed([30,11,23,4,20], 6)
    print(r)
