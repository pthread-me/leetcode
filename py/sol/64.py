#! /usr/bin/python3

class Solution:
    def minPathSum_recursive(self, A: list[list[int]]) -> int:
        
        def rec(i:int, j:int) -> int:
            cur = A[i][j]
            if i==len(A)-1 and j==len(A[i])-1:
                return cur
            elif i==len(A)-1:
                row = A[i]
                for e in row[j+1:]:
                    cur += e
                return cur
            elif j == len(A[i])-1:
                for k in range(i+1, len(A)):
                    cur += A[k][j]
                return cur
            else:
                return cur + min(rec(i+1, j), rec(i, j+1))
        
        return rec(0,0)

    def minPathSum(self, grid: list[list[int]]) -> int:
        A: list[list[int]] = [[0 for _ in grid[0]] for _ in grid]
        A[0][0] = grid[0][0]
        
        for i in range(1, len(A[0])):
            A[0][i] = grid[0][i] + A[0][i-1]
        for i in range(1, len(A)):
            A[i][0] = grid[i][0] + A[i-1][0]

        for i in range(1, len(A)):
            for j in range(1, len(A[i])):
                A[i][j] = grid[i][j] + min(A[i-1][j], A[i][j-1])

        return A[-1][-1]


if __name__ == "__main__":
    s = Solution()
    r = s.minPathSum([[1,3,1],[1,5,1],[4,2,1]])
    print(r)
