#! /usr/bin/python3
from typing import Self
        
class Solution:
    def findRepeatedDnaSequences(self, s: str) -> list[str]:
        l1: set[str] = set()
        l2: set[str] = set()

        for i in range(0, len(s)-9):
            if s[i:i+10] not in l1:
                l1.add(s[i:i+10])
            elif s[i:i+10] not in l2:
                l2.add(s[i:i+10])

        return list(l2)                
        
if __name__ == "__main__":
    S = Solution()
    a = "AAAAAAAAAAA"
    r = S.findRepeatedDnaSequences(a)
    print(r)

