#!/usr/bin/python3
class Solution:
    def canJump(self, nums: list[int]) -> bool:
        l = [False for _ in nums]
        n= len(l)
        l[n-1] = True

        # enumerate is a iterator, list() collects the elems that are then reversed
        for index, e in reversed(list(enumerate(nums[:n-1]))):
            for i in range(0,e+1):
                if index+i < n and l[index+i] == True:
                    l[index] = True
                    break
        return l[0]

if __name__ == "__main__":
    s= Solution()
    a = [3,3,3,2,1,0,4]
    b = s.canJump(a)

    print(b)
