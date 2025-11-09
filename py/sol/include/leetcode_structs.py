from typing import Self

class ListNode:
    def __init__(self, val:int=0, next:Self|None=None):
         self.val:int = val
         self.next:Self|None = next

class TreeNode:
    def __init__(self, val: int=0, left: None|Self =None, right:None|Self=None):
        self.val:int = val
        self.left:None|Self = left
        self.right: None|Self = right


