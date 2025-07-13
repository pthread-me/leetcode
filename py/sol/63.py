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
# 
# the only dif from 62.py was a change in both the base case and adding a check for obstacles
# base case: xxx1xx => 000011
# and other instance of obstacle changes the single cell to 0

class Solution:
    def uniquePathsWithObstacles(self, grid: list[list[int]]) -> int:
       
        m = len(grid)
        n = len(grid[m-1])
        
        if grid[0][0] == 1 or grid[m-1][n-1] == 1:
            return 0
                
        # mark obstacles as -1 
        for i in range(0, m):
            for j in range(0, n):
                if grid[i][j] == 1:
                    grid[i][j] = -1

        for r in grid:
            print(r)

        #setting the base case
        base_val = 1
        for i in range(m-1, -1,-1):
            if grid[i][n-1] == -1:
                base_val =0
            grid[i][n-1] = base_val
        
        base_val = 1
        for i in range(n-1, -1, -1):
            if grid[m-1][i] == -1:
                base_val = 0
            grid[m-1][i] = base_val


        for r in grid:
            print(r)
        print()
        for i in range(m-2,-1,-1):
            for j in range(n-2, -1, -1):
                # short circuit the obstacle positions
                if grid[i][j] == -1:
                    grid[i][j] = 0
                    continue

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
    res = s.uniquePathsWithObstacles([[0,1,0,0]])
    print(res)
