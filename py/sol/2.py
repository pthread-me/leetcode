#! /usr/bin/python3

# simple iterative add, just like when done on paper
from os import error
from typing import Self
# Definition for singly-linked list.
class ListNode:
    def __init__(self, val:int=0, next:Self|None=None):
        self.val:int = val
        self.next:Self | None = next


class Solution:
    def addTwoNumbers(self, l1: ListNode|None, l2: ListNode|None) -> ListNode|None:
        def add(a:int = 0, b:int = 0, flag:bool=False)-> tuple[int, bool]:
            r = a+b+1 if flag else a+b
            if r<10:
                return r, False
            else:
                return r%10, True
                

        carry:bool = False
        head = ListNode(0)
        cur = head

        while (l1 is not None) or (l2 is not None):
            if l1 is not None and l2 is not None:
                s, carry = add(l1.val, l2.val, carry)
                l1 = l1.next
                l2 = l2.next
            elif l1 is not None:
                s, carry = add(l1.val, flag=carry)
                l1 = l1.next
            else:
                s, carry = add(l2.val, flag=carry)
                l2 = l2.next
            
            cur.next = ListNode(s)
            cur = cur.next
        
        if carry:
            cur.next = ListNode(add(flag=carry)[0])
        return head.next

if __name__ == "__main__":
    l1 = ListNode(2, ListNode(4, ListNode(3)))
    l2 = ListNode(5, ListNode(6, ListNode(4)))

    cur = l1
    p: str = ""
    while cur is not None:
        p = p+ f" {cur.val}"
        cur = cur.next 
    print(p)

    cur = l2
    p = ""
    while cur is not None:
        p = p+ f" {cur.val}"
        cur = cur.next 
    print(p)




    s = Solution()
    r = s.addTwoNumbers(l1, l2)


    cur = r
    p = ""
    while cur is not None:
        p = p+ f" {cur.val}"
        cur = cur.next 
    print(p)
