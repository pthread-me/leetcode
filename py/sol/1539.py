#!/usr/bin/python3


# Dumb solution is linear, smart sol is log n
# Given an array A starting from 1 and non decreasing with no repeated values
#   if there are no missing elemens then A[m] = m-1 (zero indexed)
#   else A[m] > m-1

# the difference between them is the number of missing elements, when the diff is k we know
# what the last in value was so we add k to it
class SolutionDUMB:
    def findKthPositive(self, arr: list[int], k: int) -> int:
        c = 0
        i = 1
        p = 0

        while p <len(arr) and c<k:
            if i < arr[p]:
                c+=1
            else:
                p+=1
            i+=1

        if c == k:
            return i-1
        else:
            return (k-c) + i -1



 
class Solution:
    def findKthPositive(self, arr: list[int], k: int) -> int:
        l,r = 0, len(arr)

        while l<r:
            m = l + (r-l)//2
            if arr[m] - m - 1 < k:
                l = m+1
            else:
                r = m
        return l+k
       


if __name__ == "__main__":
    s = Solution()
    arr = [2,3,4,7,11]
    k = 5
    r = s.findKthPositive(arr, k)
    print(r)
