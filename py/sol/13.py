#! /usr/bin/python3
#from typing import Self

class Solution:
    def romanToInt(self, s: str) -> int:
        table: dict[str, int] = {"I": 1,"V": 5,"X": 10,"L": 50,"C": 100,"D": 500,"M": 1000}

        res: int = 0
        i:int = 0

        while i<len(s)-1:
            if table[s[i]] < table[s[i+1]]:
                res -= table[s[i]]
            else:
                res += table[s[i]]
            i+=1

        res += table[s[-1]] 
        return res


            

if __name__ == "__main__":
    s = Solution()
    l = "MCMXCIV"
    r = s.romanToInt(l)
    print(r)

    
