#! /usr/bin/python3


# The number of piles that alice takes should be the max of the total possible sum at that pos (i) 
# minus what bob will take, so for every pos (i,m) we calculate how much bob will take
# given he starts at pos (i+x) which is the next pos after what alice took, with m=the max of 
# m and x(which is how much alice took). we then return the max aka total - min(bob took).

# since we repeat some operations we need a top down DP table, which we fill up as we calculate new/undiscovered
# values
class Solution:
    def stoneGameII(self, piles: list[int]) -> int:

        def T(i: int, m:int)->int:
            if 2*m + i >= len(acc):
                return acc[i]
           
            if A[i][m]<0:
                vals: list[int] = []
                for x in range(1, 2*m+1):
                    vals.append(T(i+x, max(m, x)))
                A[i][m] = acc[i] - min(vals)
            
            return A[i][m] 

        acc = [sum(piles[i:]) for i in range(len(piles)-1, -1, -1)]
        acc.reverse()
        
        A: list[list[int]] = [[-1 for _ in piles] for _ in piles]
        return T(0, 1)        




if __name__ == "__main__":
    s = Solution()
    r = s.stoneGameII([2,7,9,4,4])
    print(r)
