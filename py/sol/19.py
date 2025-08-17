#! /usr/bin/python3


# a two finger walk to find the node at which the diff between i and j is n.
# then increment both (aka the window) until j is the last elem, this leaves
# i as the nth from last, so we remove it.

from os import error
from typing import Self
# Definition for singly-linked list.
class ListNode:
    def __init__(self, val:int=0, next:Self|None=None):
        self.val:int = val
        self.next:Self | None = next

class Solution:
    def removeNthFromEnd(self, head: ListNode|None, n: int) -> ListNode|None:
        def remove(cur: ListNode) -> ListNode:
            next = cur.next
            if next is None:
                raise error
            
            cur.next = next.next
            return next
        
        if head is None:
            return None

        diff: int = 0
        i:ListNode =  head
        j: ListNode = head

        while diff<n:
            if j.next == None:
                return head.next
            j = j.next
            diff += 1

        while j.next is not None:
            if i.next == None:
                raise error

            i = i.next
            j = j.next

        _ = remove(i)
        return head


if __name__ == "__main__":
    l = ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5)))))
    cur = l
    p: str = ""
    while cur is not None:
        p = p+ f" {cur.val}"
        cur = cur.next 
    print(p)
    s = Solution()
    r = s.removeNthFromEnd(l, 5)


    cur = r
    p = ""
    while cur is not None:
        p = p+ f" {cur.val}"
        cur = cur.next 
    print(p)
