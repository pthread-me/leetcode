#! /usr/bin/python3


# Two pointer walk (floyd's cycle alg)
# fast and slow pointer

class ListNode:
    def __init__(self, x:int):
         self.val:int = x
         self.next: ListNode | None = None

class Solution:
    def hasCycle(self, head: ListNode| None) -> bool:
        if head is None or head.next is None:
            return False

        slow = head
        fast = head.next

        while slow is not None and fast is not None:
            slow = slow.next
            if fast.next is None:
                return False
            fast = fast.next.next
            
            if fast == slow:
                return True

        return False
    
if __name__ == "__main__":    
    S = Solution()
    input: str = open("input.txt").read().strip()
    h = ListNode(3)
    h.next = ListNode(2)
    h.next.next = ListNode(0)
    h.next.next.next = ListNode(4)

    h.next.next.next.next = h.next

    print(S.hasCycle(h))
