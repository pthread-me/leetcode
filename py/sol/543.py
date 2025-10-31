#! /usr/bin/python3

from typing import Self


# The max diameter is the sum of the max depth of the left and right children
# we calculate this pair of maxes recursivley (once!!!) and store it in a dp table
# then return the max sum of pairs in the table

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val:int=0, left:None|Self=None, right:None|Self=None):
        self.val:int = val
        self.left: None|Self = left
        self.right: None|Self = right

class Solution:
    def diameterOfBinaryTree(self, root: None|TreeNode) -> int:
        def max_depth(x:TreeNode | None)->int:
            if x is None:
                 return 0
            elif x in table:
                return 1 + max(table[x][0], table[x][1])


            left = max_depth(x.left)
            right = max_depth(x.right)            
            table[x] = (left, right)

            return 1+ max(left, right)
             

        if root is None:
            return 0

        table: dict[TreeNode, tuple[int, int]]  = {}
        _= max_depth(root) 
        
        res = [e[0]+e[1] for e in table.values()]

        return max(res)



if __name__ == "__main__":
    S = Solution()
