#! /usr/bin/python3


# there is a better 2 pointer approach you mig want to see, tortius and hare
class Solution:
    # binary on [1..n]
    def findDuplicate(self, nums: list[int]) -> int:
        def scan(v: int):
            c = 0
            for e in nums:
                if e <= v:
                    c += 1
            return c


        n = [i for i in range(1, len(nums))]
        
        i = 0
        j = len(n)
        

        while i<j:
            mid = i+ (j-i)//2
            print(n[mid])
            if scan(n[mid]) > n[mid]:
                j = mid
            else:
                i = mid +1  

        assert(i==j)
        return n[i]

if __name__ == "__main__":
    s = Solution()
    r = s.findDuplicate([3,1,3,4,2])
    print(r)
