#!/usr/bin/python3

# We keep a monotonically increasing stack, and iterate over the letters 
# inserting them into the stack, if an elem breaks the non decreasing condition
# we try to remove the large of the 2.

# example 1432219:
# stack = []
# e = 1, stack = [1]
# e = 4, stack = [1,4]
# e = 3, here 3<4 and we have k>0 so we remove 4. then 1<3 so we just insert. stack = [1,3]
# e = 2, 2<3 and k>0 so remove 3, stack = [1,2]
# e=2, stack = [1,2,2]
# e=1, here 1<2 and k>0 so remove 2, then we try against the first 2, but k==0 so we just insert, stack = [1,2,1]
# e=9, here k==0 so stack = [1,2,1,9]


class Solution:
    def removeKdigits(self, num: str, k: int) -> str:
        stack:list[str] = []
        for e in num:
            while len(stack)>0 and stack[-1]>e and k>0:
                stack = stack[:len(stack)-1]
                k = k-1

            stack.append(e)

        res = "".join(stack).lstrip("0")
        for _ in range(0,k):
            if len(res) > 0:
                res = res[:len(res) -1]
            else:
                return "0"
        return res if len(res) > 0 else "0"

        
if __name__ == "__main__":
    s= Solution()
    r = s.removeKdigits("1432219", 3)
    print(r)
