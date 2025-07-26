#! /usr/bin/python3


# My solution was more structured, i build the tree manualy where leaf nodes are valid
# strings, the solution provided is more elegant and does not require a tree as we 
# just add the valid strings to res
# I have an old sol on leetcode but i dont remember my thought process then. i think i get it now (backtracking that is)
class Node:
    def __init__(self, s: str, opens: int, closes: int):
        self.s: str = s
        self.opens:int = opens
        self.closes: int = closes
        self.l : Node|None = None
        self.r: Node| None = None

    def T(self, n: int):
        if self.opens + self.closes >=n:
            return

        if self.opens > self.closes:
            if self.opens < n/2:
                print(f"n={n} o={self.opens} c={self.closes} -> open and close")
                self.l = Node(self.s + "(", opens= self.opens+1, closes=self.closes)
                self.r = Node(self.s + ")", opens=self.opens, closes=self.closes+1)
                self.l.T(n)
                self.r.T(n)
            else:
                print(f"n={n} o={self.opens} c={self.closes} -> close")
                self.r = Node(self.s + ")", opens=self.opens, closes=self.closes+1)
                self.r.T(n)

        elif self.opens == self.closes:
            print(f"n={n} o={self.opens} c={self.closes} -> open")
            self.l = Node(self.s + "(", opens=self.opens +1, closes=self.closes) # )
            self.l.T(n)

    
    def find_leaf(self) -> list[str]:
        if self.l == None and self.r == None:
            return [self.s]
       
        l:list[str] = []
        if (not self.r == None):
            l = l + self.r.find_leaf()

        if (not self.l == None):
            l = l + self.l.find_leaf()
        return l


class MySolution:
    def generateParenthesis(self, pairs: int) -> list[str]:
        n = pairs *2
        root: Node = Node("",0 , 0)
        root.T(n)
        l = root.find_leaf()

        return l

class Solution:
    def generateParenthesis(self, n: int) -> list[str]:
        res:list[str] = []
        def backtrack(s:str='', open:int=0, close:int=0):
            if len(s) == n*2:
                res.append(s)
                return

            if open<n:
                backtrack(s+"(", open+1, close) # )

            if open> close:
                backtrack(s+")", open, close+1)
        
        backtrack()
        return res
if __name__ == "__main__":
    S = Solution()
    r = S.generateParenthesis(4)
    print(r)

