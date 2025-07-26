#! /usr/bin/python3

# we maintain a stack that helps us remove the max of x,y in the first scan then
# the min of x,y in the second scan
class Solution:
    def maximumGain(self, s: str, x: int, y: int) -> int:
        stack: list[str] = []
        count = 0
        if x>y:
            ch1 = "a"
            ch2 = "b"
        else:
            ch1 = "b"
            ch2 = "a"
        
        for e in s:
            if len(stack) <1:
                stack.append(e)
                continue

            peak = stack.pop()
            if peak == ch1 and e == ch2:
                count += max(x,y)
            else:
                stack.append(peak)
                stack.append(e)

        s = "".join(stack)
        stack = []

        for e in s:
            if len(stack) <1:
                stack.append(e)
                continue

            peak = stack.pop()
            if peak == ch2 and e == ch1:
                count += min(x,y)
            else:
                stack.append(peak)
                stack.append(e)

        return count

if __name__ == "__main__":
    S = Solution()
    r = S.maximumGain("aabbaaxybbaabb", x=5, y=4)
    print(r)

