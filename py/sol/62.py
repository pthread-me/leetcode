#!/usr/bin/python3

# Unique Paths
#
# Given a grid and starting from 0,0 with an end pos e,e and only moving right and down
# We ue a bottom up approach asking the question, at this pos, how many unique steps are there
# at grid[e][e] there are 0. at grid[e][e-1] there is 1 and grid[e-1][e] there is 1.
# for values pos i,j the number of unique paths is the sum of the number of
# unique paths at pos grid[i+1][j] and grid[i][j+1]
#
# we start from the end and work our way to the top


class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        grid: list[list[int]] = [[0 for _ in range(0,n)] for _ in range(0,m)]
        
        if m<2 or n<2:
            return 1
        #setting the base case
        for i in range(0,m-1):
            grid[i][n-1] = 1
        for i in range(0,n-1):
            grid[m-1][i] = 1

        for i in range(m-2,-1,-1):
            for j in range(n-2, -1, -1):
                right = 0
                down = 0
                if j+1<n:
                    right = grid[i][j+1]
                if i+1<m:
                    down = grid[i+1][j]

                grid[i][j] = right + down
        
        return grid[0][0]

if __name__ == "__main__":
    s= Solution()
    n = 3
    res = s.uniquePaths(3,7)
    print(res)
