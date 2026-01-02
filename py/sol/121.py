#! /usr/bin/python3

# using kadane's algoritm on the prefix sum of the prices

class Solution:
    def maxProfit(self, prices: list[int]) -> int:
        if len(prices) <= 1:
            return 0

        p: list[int] = [(prices[i] - prices[i-1]) for i in range(1, len(prices))]    

        maxP: int = p[0]
        cur: int = p[0]
        for i in range(1, len(p)):
            if cur>=0:
                cur += p[i]
            else:
                cur = p[i]
            if maxP < cur:
                maxP = cur

        return maxP if maxP > 0 else  0

if __name__ == "__main__":
    s = Solution()
    r = s.maxProfit([7,1,5,3,6,4])
    print(r)
