#! /usr/bin/python3

# using kadane's algoritm on the prefix sum of the prices

class Solution:
    def maxProfit(self, prices: list[int]) -> int:
        prefix_sum = [0] + [prices[i] - prices[i-1] for i in range(1, len(prices))]    

        if all([e>-1 for e in prefix_sum]):
            return sum(prefix_sum)
        elif all([e<0 for e in prefix_sum]):
            return min(prefix_sum)

       
        best = 0
        cur = 0
       
        for e in prefix_sum:
            cur = max(cur + e, e)
            best = max(best, cur)

        return best

    

if __name__ == "__main__":
    s = Solution()
    r = s.maxProfit([7,1,5,3,6,4])
    print(r)
