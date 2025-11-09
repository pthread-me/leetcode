#! /usr/bin/python3
from typing import Self

class Solution:
    def isIsomorphic(self, s: str, t: str) -> bool:
        if len(s) != len(t):
            return False

        s_to_t: dict[str, str] = {}
        t_to_s: dict[str, str] = {}

        for i in range(len(s)):
            if s[i] not in s_to_t and t[i] not in t_to_s:
                s_to_t[s[i]] = t[i]
                t_to_s[t[i]] = s[i]
            else:
                if s[i] in s_to_t and s_to_t[s[i]] != t[i]:
                    return False
                elif t[i] in t_to_s and t_to_s[t[i]] != s[i]:
                    return False

                    
        return True


              
if __name__ == "__main__":
    S = Solution()
    s: str = "egg"
    t:str = "baba"
    r = S.isIsomorphic(s,t)
    print(r)

