#! /usr/bin/python3

class Solution:
    def countGoodSubstrings(self, s: str) -> int:
        if len(s) < 3:
            return 0

        count:int = 0
        
        for i in range(0, len(s) -2):
            if not (s[i] == s[i+1] or s[i] == s[i+2] or s[i+1] == s[i+2]):
                count += 1

        return count

if __name__ == "__main__":
    s = Solution()
    r = s.countGoodSubstrings("aababcabc")
    print(r)
