#! /usr/bin/python3

import math

# Definition for singly-linked list.
class ListNode:
     def __init__(self, val=0, next=None):
         self.val:int = val
         self.next:ListNode|None = next


def P(h: ListNode| None) -> None:
    if h is None:
        return 

    cur = h
    print(f"Print")
    while not cur is None:
        print(f"\t{cur.val}")
        cur = cur.next


class Solution:
    def reorderList(self, head: ListNode|None) -> None:
        if head is None or head.next is None:
            return

        stack: list[ListNode] = []
        cur = head
        while cur is not None:
            stack.append(cur)
            cur = cur.next

        stack = stack[math.ceil(len(stack)/2):]
        for e in stack:
            e.next = None

        cur = head
        while cur is not None:
            if cur.next == stack[0]:
                cur.next = None
                break
            cur = cur.next

        cur = head
        while cur is not None and len(stack) > 0:
            l = stack.pop()
            s = cur.next

            cur.next = l
            l.next = s
            cur = s
        

if __name__ == "__main__":    
    S = Solution()
    input: str = open("input.txt").read().strip()
    h = ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5, None)))))
    S.reorderList(h)
   


