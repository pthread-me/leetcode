#!/usr/bin/python3

class Solution:
    def isAnagram(self, s: str, t: str) -> bool:
        if not len(s) == len(t):
            return False
        h: list[int] = [0 for _ in range(0, 26)]
        
        for i in range(0, len(s)):
            e1 = s[i]
            e2 = t[i]
            h[ord(e1)-97] +=1
            h[ord(e2)-97] -=1

        res = map(lambda e: e==0, h)
        return all(res)

if __name__ == "__main__":
    s= Solution()
    r = s.isAnagram("anagram", "nagaram")
    print(r)
