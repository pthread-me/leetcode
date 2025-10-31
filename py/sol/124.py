#! /usr/bin/python3
from typing import Self


# Just memoization, save the max that any node as a root can hold in an array
# and return the max that a path can pass through that node without it being a root
# then return the max of the array
# the return is used to calculate the array entry for the parent


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val:int=0, left:Self|None= None, right:Self|None = None):
        self.val:int = val
        self.left:Self|None = left
        self.right:Self|None = right

class Solution:
    def maxPathSum(self, root: TreeNode | None) -> int:
        if root is not None and root.left == None and root.right == None:
            return root.val

        l:list[int] = []
        _ = self.rec(root, l)

        return max(l) 

    def rec(self, root: TreeNode|None, roots:list[int])->int:
        if root is None:
            return 0

        left: int = self.rec(root.left, roots)
        right: int = self.rec(root.right, roots)
            
        
        roots.append(max(root.val, root.val + left, root.val + right, root.val + left + right))    
        return max(root.val, root.val + left, root.val + right)



if __name__ == "__main__":
    s = Solution();
    t = TreeNode(-10, TreeNode(9), TreeNode(20, TreeNode(15), TreeNode(7)))
    r = s.maxPathSum(t)
    print(r)
