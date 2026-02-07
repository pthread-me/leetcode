#!/usr/bin/python

import math

class Solution:
    def countAndSay(self, n: int) -> str:
        s: str = "1"
        for _ in range(0, n-1):
            i: int = 0
            freq: int = 1
            cur = ""

            while i<len(s):
                if i+1 < len(s) and s[i]==s[i+1]:
                    freq += 1
                else:
                    cur += (str(freq) + s[i]) 
                    freq = 1

                i += 1

            s = cur
        return s

if __name__ == "__main__":
    S: Solution = Solution()
    n: int = 4
    r = S.countAndSay(n)
    print(r)
    
