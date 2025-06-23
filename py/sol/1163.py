class Solution:
    def lastSubstring(self, s: str) -> str:
        if len(s)<2:
            return s

        i = 0
        j = 1
        k = 0

        while(j+k<len(s)):
            if s[i+k] < s[j+k]:
                i = max(i+k, j)
                j = i+1
                k = 0
            elif s[i+k] == s[j+k]:
                k= k+ 1
            else:
                j = j+ k + 1
                k = 0
        return s[i:]

if __name__ == "__main__":
    s = Solution()
    res = s.lastSubstring("leetcotde")
    print(res)
