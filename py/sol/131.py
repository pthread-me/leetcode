#! /usr/bin/python3
#from typing import Self


class Solution:
    def partition(self, s: str) -> list[list[str]]:
        res: list[list[str]]= [] 
        
        def is_pal(x: str):
           for i in range(0, len(x)//2):
                if x[i] != x[len(x)-i-1]:
                    return False
           return True

        def backtrack(temp:list[str], i:int):
            if i == len(s):
                if is_pal(temp[-1]):
                    res.append(temp[:])
                return

            if len(temp) > 0: 
                temp[-1] = temp[-1]+s[i]
                backtrack(temp, i+1)
                temp[-1] = temp[-1][:-1]

            if len(temp) == 0 or is_pal(temp[-1]):
                temp.append(s[i])
                backtrack(temp, i+1)
                _ = temp.pop()
        
        backtrack([], 0)
        return res


if __name__ == "__main__":
    s = Solution()
    l = "aab"
    r = s.partition(l)
    print(r)

    
