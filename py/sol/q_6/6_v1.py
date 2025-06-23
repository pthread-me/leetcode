#!/usr/bin/python3
import math

class Solution:
    
        def convert(self, s: str, numRows: int) -> str:
            if numRows == 1:
                return s


            n = (numRows)*2 - 2
            res: list[list[str]] = [ [] for i in range(0, numRows)]

            for r in range(0, math.ceil(n/2)+1):
                for i, e in enumerate(s):
                    if i%n == r or i%n == n-r:
                        print(f'i: {i}\te: {e}')
                        res[r].append(e)
           
            s_res = ""
            for r in res:
                for i in r:
                    s_res = s_res + i
            
            return s_res

if __name__ == "__main__":
    S = Solution()
    s: str = "paypalishiring"
    n: int = 3
    res = S.convert(s, n)
    print(res)
