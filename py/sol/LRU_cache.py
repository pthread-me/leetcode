#! /usr/bin/python3


# LRU cache implementation using a double linked list, and a hashtable of key to node pointer

from typing import Self

class Node:
    key: int
    val: int
    next: Self | None
    prev: Self | None

    def __init__(self, key: int, val:int):
        self.key = key
        self.val = val
        self.next = None
        self.prev = None


class LRUCache:
        
    head: Node | None
    tail: Node | None
    capacity: int
    size: int
    table: dict[int, Node]

    def __init__(self, capacity: int):
        self.head = None
        self.tail = None
        self.table = {}
        self.capacity = capacity
        self.size = 0



    def push(self, n:Node):
        if self.head is None and self.tail is None:
            self.head = n
            self.tail = n
        else:
            assert(self.head is not None)
            o = self.head
            n.next = o
            o.prev = n
            self.head = n

        self.size += 1

    
    def extract(self, n:Node):
        assert(n is not None)

        if self.size == 1:
            self.head = None
            self.tail = None
        elif n == self.head:
            next = n.next
            n.next = None
            next.prev = None
            self.head = next
        elif n == self.tail:
            prev = n.prev
            prev.next = None
            n.prev = None
            self.tail = prev
        else:
            prev = n.prev
            next = n.next
            prev.next = next
            next.prev = prev
            n.next = None
            n.prev = None

        self.size -= 1



    def pop(self) -> Node | None:
        if self.head is None and self.tail is None:
            return None

        assert(self.tail is not None)
        assert(self.tail.next is None)

        n = self.tail
        o = n.prev
        if o is None:
            self.head = None
            self.tail = None
        else:
            o.next = None
            n.prev = None
        
        self.tail = o
        self.size -= 1

        return n

    def get(self, key: int) -> int:
        if key in self.table:
            n = self.table[key]
            if n is not self.head:
                self.extract(n)
                self.push(n)
            return n.val
        else: 
            return -1

    def put(self, key: int, val:int):
        if self.capacity == 0:
            return

        # no insertion
        if key in self.table:
            self.table[key].val = val
            n = self.table[key]
            if n is not self.head:
                self.extract(n)
                self.push(n)

            return
        
        if self.capacity == self.size:
            print(f"pop on putting {key}")
            r = self.pop()
            assert(r is not None)
            print(r.key, self.table)
            _= self.table.pop(r.key)


        n = Node(key, val)
        self.push(n)
        self.table[key] = n
       
    
    def p(self):
        s = ""
        cur = self.head
        while cur is not None:
            cur_val = cur.val
            cur_key = cur.key
            s = s + f"[{cur_key, cur_val}, {cur.key in self.table}]"
            cur = cur.next
        return s


# Your LRUCache object will be instantiated and called as such:
# obj = LRUCache(capacity)
# param_1 = obj.get(key)
# obj.put(key,value)

if __name__ == "__main__":
    cache = LRUCache(2)
    cache.put(2,1)
    cache.put(1,1)
    cache.put(2,3)
    cache.get(2)
