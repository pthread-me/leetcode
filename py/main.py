#! /usr/bin/python3

# Use a stack for iterative reversal
# we can also use the call stack as the, well, stack. via recursion


from typing import Self


#Definition for singly-linked list.
class ListNode:
    def __init__(self, val: int=0, next:Self|None=None):
        self.val:int = val
        self.next: Self | None = next

class Solution:
    def iter_reverseList(self, head: ListNode | None) -> ListNode | None:
        if head is None:
            return
        stack: list[ListNode] = []

        cur:ListNode | None = head
        while cur is not None:
            stack.append(cur)
            cur = cur.next
            stack[-1].next = None

        new_head = stack.pop()
        cur = new_head
        while len(stack) > 0:
            cur.next = stack.pop()
            cur = cur.next

        return new_head


    def reverseList(self, head: ListNode | None) -> ListNode | None:
        if head == None:
            return
        new_head = self.T(head, head)[1] 
        head.next = None
        
        return new_head

    def T(self, head: ListNode, origin: ListNode) -> tuple[ListNode, ListNode]:
        if head.next == None:
            return (head, head)

        res = self.T(head.next, origin)
        res[0].next = head
        origin = res[1]
         
        return (head, origin)


    
if __name__ == "__main__":    
    S = Solution()
    input: str = open("input.txt").read().strip()
    h = ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5, None)))))
    h = S.reverseList(h)

    cur = h
    while cur is not None:
        print(cur.val)
        cur = cur.next
   


