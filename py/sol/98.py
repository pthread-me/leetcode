#! /usr/bin/python3

from typing import Self


# We start with a range of possible values being -inf and +inf
# with every traversal the range shrinks
# if any node breaks the range then the tree is not valid


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val:int=0, left:None|Self=None, right:None|Self=None):
        self.val:int = val
        self.left: None|Self = left
        self.right: None|Self = right

class Solution:
    def isValidBST(self, root: None|TreeNode) -> bool:
        def rec(x: TreeNode|None, l: float, h: float) -> bool:
            if x is None:
                return True

            if l < x.val < h:
                return rec(x.left, l, min(x.val, h)) and rec(x.right, max(l, x.val), h)
            else:
                return False

        
        return rec(root, float('-inf'), float('inf'))



if __name__ == "__main__":
    S = Solution()
    t = TreeNode(5, TreeNode(1, None, TreeNode(4)), TreeNode(7))
    r = S.isValidBST(t)
    print(r)
