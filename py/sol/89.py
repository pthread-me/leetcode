#! /usr/bin/python3
from math import ceil 

# my backtracking solution is coorect but too slow, gray codes have a formula
# i^(i>>1) for i in [0,2^n)

class SolutionDUMB:
    def grayCode(self, n: int) -> list[int]:
        m: int = 2**n 
        res: list[list[str]] = []
        
        def bt(temp: list[str]):
            if len(res) > 0:
                return
            if len(temp) == m:
                if sum(1 if e == "1" else 0 for e in temp[-1]) == 1:
                    res.append(temp[:])
                return

            last = list(temp[-1][:])

            for i in range(len(last)):
                last[i] = "0" if last[i]=="1" else "1"
                if "".join(last) in temp:
                    last[i] = "0" if last[i]=="1" else "1"
                    continue

                temp.append("".join(last))
                bt(temp)

                _ = temp.pop()
                last[i] = "0" if last[i]=="1" else "1"

        bt(["0"*n])
        print(res)
        return [int(e, 2) for e in res[0]]



class Solution:
    def grayCode(self, n: int) -> list[int]:
        res: list[int] = []
        for i in range(0, 2**n):
            res.append(i^(i>>1))

        return res
        
if __name__ == "__main__":
    S = Solution()
    r = S.grayCode(2)
    print(r)

     
