#! /usr/bin/python3
from include.leetcode_structs import *

class Solution:
    def simplifyPath(self, path: str) -> str:
        p = [e for e in path.split("/") if e != ""]
        s : list[str] = [] 
        
        for e in p:
            if e == ".":
                continue
            elif e == "..":
                if len(s) > 0: _ = s.pop()
            else:
                s.append(e)

        
        if len(s) == 0:
            return "/"

        res: str = ""
        for e in s:
            res = res + "/" + e

        
        return res




if __name__ == "__main__":
    S= Solution()
    l = "/../"
    r = S.simplifyPath(l)
    print(r)
    
