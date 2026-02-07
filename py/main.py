#!/usr/bin/python

import math
class Solution:
    def longestValidParentheses(self, s: str) -> int:
        s = s.lstrip(")").rstrip("(") # )

        max_size = 0
        count: int = 1
        size: int = 1
        
        i: int = 0
        j: int = 1

        while j < len(s):
            if s[j] == "(": #)
                size += 1
                count += 1
                continue

            count -= 1
            if count == 0 and size > max_size:
                max_size = size
                i+=1
                j = i+1
            elif count < 0:
                while i<len(s) and s[i] == ")":
                    i += 1
                count = 1
                size = 1
                j = i+1
            else:
                j+=1
                size += 1

        return max_size

if __name__ == "__main__":
    S: Solution = Solution()
    s: str = ")()())"

    r = S.longestValidParentheses(s)
    print(r)
    
