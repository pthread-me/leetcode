#! /usr/bin/python3

from leetcode_structs import *

class Solution:
    def sortList(self, head: ListNode|None) -> ListNode|None:
        def merge(l1:ListNode|None, l2: ListNode|None)->ListNode|None:
            dummy: ListNode = ListNode(-0)
            cur: ListNode = dummy
            while l1 and l2:
                if l1.val < l2.val:
                    cur.next = l1
                    l1 = l1.next
                else:
                    cur.next = l2
                    l2 = l2.next
                cur = cur.next

            if l1: cur.next = l1
            if l2: cur.next = l2

            return dummy.next

        def rec(h: ListNode|None) -> ListNode|None:
            if not h or not h.next:
                return h


            prev = None
            slow = h
            fast = h
            while fast and fast.next:
                prev = slow
                slow = slow.next 
                fast = fast.next.next

            prev.next = None

            left = rec(h)
            right = rec(slow)

            return merge(left, right)
 

        return rec(head) 
       

if __name__ == "__main__":
    S= Solution()
    l = ListNode(4, ListNode(2, ListNode(1, ListNode(3)))) 
    r = S.sortList(l) 

    c = r
    while c is not None:
        print(c.val)
        c = c.next

