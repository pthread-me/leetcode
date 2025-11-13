#! /usr/bin/python3
from include.leetcode_structs import *
import heapq

# this is not in place, since we answer seperatly then copy
# link has an inplace solution: https://leetcode.com/problems/rotate-image/solutions/18872/a-common-method-to-rotate-the-image-by-s-tygg/

class Solution:
    def rotate(self, matrix: list[list[int]]) -> None:
        """
        Do not return anything, modify matrix in-place instead.
        """
        
        A: list[list[int]] = [[-1 for _ in matrix[0]] for _ in matrix]

        for i in range(0, len(matrix[0])):
            for j in range(0, len(matrix)):
                A[j][~i] = matrix[i][j]

        for i in range(0, len(matrix[0])):
            for j in range(0, len(matrix)):
                matrix[i][j] = A[i][j]




if __name__ == "__main__":
    S= Solution()
    m = [[1,2,3],[4,5,6],[7,8,9]]
    for e in m:
        print(e)
    _ = S.rotate(m)
    print()
    for e in m:
        print(e)
    
