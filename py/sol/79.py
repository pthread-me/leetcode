#! /usr/bin/python3
#from typing import Self

# find the first charachter, then start backtracking until all chars are found or
# we short circuit to a false
# if one is found we return immediattly

class Solution:
    def exist(self, board: list[list[str]], word: str) -> bool:
        dir: list[tuple[int, int]] = [(-1, 0), (0, -1), (0, 1), (1, 0)]        

        def backtrack(x:int, y:int ,n:int) -> bool:
            if n==len(word):
                return True
            res: bool = False

            for (d1, d2) in dir:
                if -1<x+d1<len(board) and -1<y+d2<len(board[0]):
                    if  board[x+d1][y+d2] == word[n]:
                        old:str = board[x][y] + ""
                        board[x][y] = "."
                        res = backtrack(x+d1, y+d2, n+1)
                        board[x][y] = old

                if res == True:
                    break

            return res

        res: bool = False
        for i in range(0, len(board)):
            for j in range(0, len(board[0])):
                if board[i][j] == word[0]:
                    res = backtrack(i, j, 1)
                
                if res == True:
                    return res

        return res

if __name__ == "__main__":
    s = Solution()
    board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]]
    for r in board:
        print(r)


    word = "ABCESE"
    r = s.exist(board, word)
    print(r)

    
