#! /usr/bin/python3

# Simple recursive function

from typing import Self

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val: int=0, left: None|Self =None, right:None|Self=None):
        self.val:int = val
        self.left:None|Self = left
        self.right: None|Self = right

class Solution:
    def invertTree(self, root: TreeNode|None) -> TreeNode|None:
        if root is None:
            return
    
        temp = self.invertTree(root.right)
        root.right = self.invertTree(root.left)
        root.left = temp
        return root

if __name__ == "__main__":
    s = Solution()
