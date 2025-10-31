#! /usr/bin/python3
#from typing import Self
        
        

class Solution:
    def combinationSum(self, candidates: list[int], target: int) -> list[list[int]]:
        candidates = list(set(candidates))
        dp: list[list[list[int]]] = [ [] for _ in range(target+1)]
        
        def back_search(n: int) -> list[list[int]]:
            res: list[list[int]] = []
            for i in range(1, n//2+1):
                if len(dp[i]) > 0 and len(dp[n-i])>0:
                    for e1 in dp[i]:
                        for e2 in dp[n-i]:
                            t = sorted(e1+e2)
                            if t not in res:
                                res.append(t)

            return res

        for i in range(1, target+1):
            if i in candidates:
                dp[i] = [[i]]
            dp[i] = dp[i] + back_search(i)
            #print(f"n: {i} -> {dp[i]}")
        
        
        return dp[target]






if __name__ == "__main__":
    s = Solution()
    l = [2,3,6,7]
    r = s.combinationSum(l, 7)
    print(r)
