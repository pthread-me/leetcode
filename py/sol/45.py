#!/usr/bin/python3

class Solution:
    def jump(self, nums: list[int]) -> int:
        l = [float('inf') for _ in nums]
        n = len(l)
        
        l[n-1] = 0

        for i, e in reversed(list(enumerate(nums[:n-1]))):
            if e == 0:
                continue
            if i + e == n-1:
                l[i] = 1
                continue
            l[i] = 1+ min([l[i+j] for j in range(0, e+1) if i+j<n])
        
        return int(l[0])
    
if __name__ == "__main__":
    s= Solution()
    a = [2,3,0,1,4]
    b = s.jump(a)

    print(b)
