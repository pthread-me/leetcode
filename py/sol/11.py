#! /usr/bin/python3

# I truly cant believe how long it took me to get this, was hyper fixated on FINDING
# the index but that doesnt matter, ffs im so dumb i literally hate myself so much rn like just kill urself dude :|

# recursive
def rec(height: list[int], i: int, j:int):
    cur: tuple[int, int, int] = (min(height[i], height[j]) * (j-i), i, j)
    if i+ 1 >= j:
        return cur
    
    left = rec(height, i+1, j)
    right = rec(height, i, j-1)

    return max(cur, left, right, key=lambda x: x[0])

# n^2 solution
def n_squared(height: list[int])-> int:
    A: list[int] = [-1] * (len(height))
    for i in range(0, len(height)):
        A[i] = max([min(height[i], height[j]) * (j-i) for j in range(i, len(height))])

    return max(A) 


class Solution:
    def maxArea(self, height: list[int]) -> int:
        i = 0
        j = len(height) -1
        max_area = min(height[i], height[j]) * (j-i)

        while i<j:
            if height[i] < height[j]:
                i += 1
            else:
                j-=1

            max_area = max(max_area, min(height[i], height[j]) * (j-i) )
         
        return max_area

if __name__ == "__main__":
    s= Solution()
    r = s.maxArea([1,8,6,2,5,4,8,3,7])
    print(r)
