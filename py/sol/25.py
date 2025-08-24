#! /usr/bin/python3

# A two pointer walk on the list to break it into segments of size K, each segment is reversed in place
# using a stack. then the segment is linked back to the original list, continue until we cant form a segment of 
# size k


from typing import Self

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val: int=0, next: None | Self =None):
        self.val:int = val
        self.next:Self|None = next

class Solution:
    def reverseKGroup(self, head: ListNode|None, k: int) -> ListNode|None:
        def rev(s: ListNode, e: ListNode)-> tuple[ListNode, ListNode]:
            stack: list[ListNode] = []
            
            cur = s
            while cur is not e:
                assert(cur is not None)

                stack.append(cur)
                temp = cur.next
                cur.next = None
                cur = temp
            
            e.next = None
            stack.append(e)

            
            s = stack.pop()
            cur = s
            while len(stack)>0:
                cur.next = stack.pop()
                cur = cur.next

            e = cur 

            cur = s
            return (s,e)



        
        if head is None:
            return head
       
        first:bool = True
        prev:ListNode|None = None
        next: ListNode|None = None
        
        start: ListNode|None = head
       
        while True:
            if start is None: 
                return head

            end: ListNode|None = start
            for _ in range(0, k-1):
                if end.next is not None:
                    end = end.next
                else:
                    return head
            next = end.next 
            
            s,e = rev(start, end)
            

            if first:
                head = s
                first = False
            elif prev is not None:
                prev.next = s
            
            prev = e
            e.next = next
            start = next 

if __name__ == "__main__":
    s = Solution()
    l = ListNode(1, ListNode(2, ListNode(3, ListNode(4,ListNode(5)))))

    old = ""
    new = ""
    
    cur = l
    while cur is not None:
        old = f"{old}{cur.val}"
        cur = cur.next
 

    r = s.reverseKGroup(l, 3)
    
    while r is not None:
        new = f"{new}{r.val}"
        r = r.next


    print(f"old: {old}")
    print(f"new: {new}")
