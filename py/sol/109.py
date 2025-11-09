#! /usr/bin/python3
from typing import Self

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val:int=0, next:Self | None=None):
        self.val:int = val
        self.next:Self | None = next


class TreeNode:
    def __init__(self, val:int=0, left:Self | None=None, right:Self|None=None):
         self.val:int = val
         self.left:Self | None = left
         self.right:Self | None = right



class Solution:
    def sortedListToBST(self, head: ListNode|None) -> TreeNode | None:
        def rec(s: ListNode|None, n: int):
            print("s:", s.val if s is not None else None, n)
            if n <= 0 or s is None:
                return None
            elif n==1:
                return TreeNode(s.val)
            elif n == 2:
                head: TreeNode = TreeNode(s.val)
                head.right = TreeNode(s.next.val) if s.next is not None else None
                return head
            
            cur:ListNode|None = s
            for _ in range(n//2):
                if cur is None:
                    exit("cur cant be none")
                cur = cur.next 
            
            if cur is None:
                exit("cur cant be none - out of loop")

            head: TreeNode = TreeNode(cur.val)
            lc, rc = n//2,0

            if n%2 == 1:
                rc = n//2
            else:
                rc = n//2 -1

            head.left = rec(s, lc)
            head.right = rec(cur.next, rc)

            return head
        
        if head is None:
            return None

        count: int = 0
        c:ListNode | None = head
        while c is not None:
            count +=1 
            c = c.next

        
        return rec(head, count)
                

if __name__ == "__main__":
    S= Solution()
    l = ListNode(-10, ListNode(-3, ListNode(0, ListNode(5, ListNode(9)))))
    r = S.sortedListToBST(l)
    print(r.val, r.left.val)
