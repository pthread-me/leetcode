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
    def maxDepth(self, root: TreeNode|None) -> int:
        if root is None:
            return 0

        return 1 + max(self.maxDepth(root.left), self.maxDepth(root.right))

        
if __name__ == "__main__":
    s = Solution()
