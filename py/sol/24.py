#! /usr/bin/python3
from include.leetcode_structs import *

class Solution:
    def swapPairs(self, head: ListNode|None) -> ListNode|None:
        if head is None or head.next is None:
            return head

        i: ListNode|None = head
        j: ListNode|None = head.next
        head = j

        while j is not None:
            assert(i is not None)
            ni: ListNode| None = j.next
            nj: ListNode| None = j.next.next if j.next is not None else None

            i.next = nj if nj is not None else ni  
            j.next = i
            
            i = ni if nj is not None else nj
            j = nj

        return head

                                

