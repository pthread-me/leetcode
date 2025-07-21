#! /usr/bin/python3

# 2 pointer walk
class Solution:
    def isPalindrome(self, s: str) -> bool:
        s = "".join([c.lower() for c in s if c.isalnum()])
        if len(s) == 0:
            return True

        i = 0
        j = len(s) -1
        while  i < j:
            if s[i] == s[j]:
                i+=1
                j-=1
            else:
                return False

        return True

if __name__ == "__main__":
    s= Solution()
    r = s.isPalindrome("a a")
    print(r)
