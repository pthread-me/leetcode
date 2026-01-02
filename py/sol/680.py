#! /usr/bin/python3
  

class Solution:
    def validPalindrome(self, s: str) -> bool:

        def rec(i:int, j:int, can_skip: bool)->bool:
            while(i<j):
                if s[i] != s[j]:
                    if  can_skip:
                        can_skip = False
                        path1 = rec(i+1, j, False)
                        path2 = rec(i, j-1, False)
                        return path1 or path2
                    else:
                        return False
                i+=1
                j-=1

            return True

        return rec(0, len(s)-1, True)


if __name__ == "__main__":
    S = Solution()
    s = "abccba"

     
