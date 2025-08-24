#! /usr/bin/python3

# Normal merge sort

from typing import Self

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val:int =0, next: Self | None= None):
        self.val:int  = val
        self.next: Self | None = next

class Solution:
    def mergeTwoLists(self, list1: ListNode | None, list2: ListNode | None) -> ListNode | None:
        if list1 is None:
            return list2
        elif list2 is None:
            return list1


        l1: ListNode | None = list1
        l2: ListNode | None = list2
        head:ListNode | None = None
       
        
        if l1.val < l2.val:
            head = l1
            l1 = l1.next
        else:
            head = l2
            l2 = l2.next

        cur = head

        while l1 is not None and l2 is not None:
            if l1.val < l2.val:
                cur.next = l1
                l1 = l1.next
            else:
                cur.next = l2
                l2 = l2.next

            cur = cur.next

        while l1 is not None:
            cur .next = l1
            l1 = l1.next
            cur = cur.next

        while l2 is not None:
            cur .next = l2
            l2 = l2.next
            cur = cur.next
        
        return head

if __name__ == "__main__":
    s = Solution()
    l1 = ListNode(1, ListNode(2, ListNode(3)))
    l2 = ListNode(1, ListNode(3, ListNode(3)))
    
    head= s.mergeTwoLists(l1, l2)
    f = ""
    while head is not None:
        f = f"{f} {head.val}"
        head = head.next    
    print(f)
