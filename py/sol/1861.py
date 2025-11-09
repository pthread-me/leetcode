#! /usr/bin/python3
from include.leetcode_structs import *

# We shift stones first then rotate

class Solution:
    def rotateTheBox(self, boxGrid: list[list[str]]) -> list[list[str]]:
        stone = "#"
        obs = "*"

        for r in boxGrid:
            jump_pos = len(r) -1
            for j in range(len(r)-1, -1, -1):
                if r[j] == obs:
                    jump_pos = j-1
                elif r[j] == stone:
                    r[j], r[jump_pos] = r[jump_pos], r[j]
                    jump_pos -= 1

        for r in boxGrid:
            print(r)
        res: list[list[str]] = [["" for _ in range(len(boxGrid))] for _ in range(len(boxGrid[0]))]

        for i in range(0, len(boxGrid)):
            for j in range(0, len(boxGrid[0])):
                res[j][~i] = boxGrid[i][j]
        
        return res


if __name__ == "__main__":
    S= Solution()
    l = boxGrid = [["#","#","*",".","*","."],["#","#","#","*",".","."],["#","#","#",".","#","."]] 
    r = S.rotateTheBox(l)
    print("result:")
    for e in r:
        print(e)
    
