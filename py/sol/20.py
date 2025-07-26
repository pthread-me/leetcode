#! /usr/bin/python3


class Solution:
    def isValid(self, s: str) -> bool:
        opens = ["(", "{", "["]
        closes = [")", "}", "]"]

        stack: list[str] = []

        for e in s:
            if e in opens:
                stack.append(e)
            else:
                if len(stack) < 1 or not closes.index(e) == opens.index(stack.pop()):
                    return False

        if len(stack) > 0:
            return False
        else:
            return True
        

if __name__ == "__main__":
    S = Solution()
    r = S.isValid("([])")
    print(r)

