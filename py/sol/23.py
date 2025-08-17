#! /usr/bin/python3

from typing import Self
import heapq

# We use a heap to keep track of the ordering and a hashtable to maintain a count
# then just pop e from table and add as much as the freq is to the new list

#Definition for singly-linked list.
class ListNode:
    def __init__(self, val:int=0, next:None|Self=None):
        self.val:int = val
        self.next: None|Self = next

class Solution:
    def mergeKLists(self, lists: list[ListNode | None]) -> ListNode | None:
        if len(lists) <1:
            return None

        table: dict[int, int] = {}
        heap: list[int] = []
        

        for l in lists:
            while l is not None:
                if l.val not in table:
                    heapq.heappush(heap, l.val)

                table[l.val] = table.get(l.val, 0) + 1
                l = l.next
        
        res: ListNode| None = None
        prev = res
    
        while len(heap) > 0:
            e: int = heapq.heappop(heap)
            freq:int = table[e]
             
            for _ in range(0, freq):
                cur = ListNode(e)
                if prev is None:
                    prev = cur
                    res = prev
                else:
                    prev.next = cur
                    prev = cur
        return res

if __name__ == "__main__":
    s = Solution()
    l1 = ListNode(0, ListNode(1, ListNode(2, ListNode(3, None))))
    l2 = ListNode(0, ListNode(1, ListNode(8, ListNode(10, None))))
    r = s.mergeKLists([l1, l2])

    while r is not None:
        print(r.val)
        r = r.next
