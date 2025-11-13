#! /usr/bin/python3
from include.leetcode_structs import *

class Solution:
    def numIslands(self, grid: list[list[str]]) -> int:
        dir: list[tuple[int, int]] = [(1,0), (-1,0), (0,-1), (0, 1)]
        A: list[list[int]] = [[0 for _ in grid[0]] for _ in grid]
        res: int = 0 

        def dfs(i:int, j:int):
            A[i][j] = 1
            for (x,y) in dir:
                if -1<i-x<len(grid) and -1<j-y<len(grid[0]) and grid[i-x][j-y] == "1" and A[i-x][j-y] != 1:
                    dfs(i-x, j-y)
            
        for i in range(0, len(grid)):
            for j in range(0, len(grid[0])):
                if grid[i][j] == "1" and A[i][j] == 0:
                    print(i,j)
                    res += 1
                    dfs(i,j)

        return res
                    
if __name__ == "__main__":
    S= Solution()
    grid = [["1","0","1","1","1"],["1","0","1","0","1"],["1","1","1","0","1"]]
    r= S.numIslands(grid)
    print(r)
