#! /usr/bin/python3



class SegmentTree:
    src: list[int]
    tree: list[int]
    
    def __init__(self, src:list[int]):
        self.src = src
        self.tree = [0] * len(src) * 4
        self.__build__(0, 0, len(src)-1)

    def __build__(self, v: int, l: int, r:int):
        if l==r:
            self.tree[v] = self.src[l]
            return


        mid = l+ (r-l)//2
        self.__build__(2*v+1, l, min(r, mid))
        self.__build__(2*v+2, max(mid+1, l), r)
        self.tree[v] = max(self.tree[2*v+1], self.tree[2*v+2])
        
    def query(self, v:int, l:int, r:int, tl:int, tr:int)-> int:
        # return 0 cause we only query sum
        if l>r or l<0 or r>len(self.tree):
            return 0
        
        if l==tl and r==tr:
            #print(f"found {l}, {r}: {self.tree[v]}")
            return self.tree[v]

        
        tm = tl + (tr-tl)//2
        #print(f"went :{tl, tm} for {l, min(tm, r)} and  {tm+1, tr} for {max(tm+1, l), r}")
        return self.query(v*2+1, l, min(tm, r), tl, tm ) + self.query(v*2+2, max(tm+1, l), r, tm+1, tr)
    def update(self, i:int, val:int):
        if i>=len(self.src):
            return

        self.src[i] = val
        self.__update__(0, 0, len(self.src)-1, i, val)

    def __update__(self, v:int, l: int, r: int, i: int, val: int):
        if l==r and l == i:
            self.tree[v] = val
            return

        mid = l+(r-l)//2
        if i<=mid:
            self.__update__(2*v+1, l, mid, i, val)
        else:
            self.__update__(2*v+2, mid+1, r, i, val)

        self.__build__(v, l, r)
    
    def leetcode(self, v:int, l:int, r:int, val:int)-> int:
        if self.tree[v] < val:
            return -1

        if l == r and self.tree[v]>=val:
            return self.tree[v]

        mid = l+(r-l)//2
        if self.tree[2*v+1]>= val:
            return self.leetcode(2*v+1, l, mid, val)
        else:
            return self.leetcode(2*v+2, mid+1, r, val)


class Solution:
    def numOfUnplacedFruits(self, fruits: list[int], baskets: list[int]) -> int:
        tree = SegmentTree(baskets)
        count: int = 0
        for e in fruits:
            found = tree.leetcode(0, 0, len(fruits)-1, e)
            if found > -1:
                i = tree.src.index(found)
                tree.update(i, -1)
            else:
                count += 1
        return count


if __name__ == "__main__":
    s = Solution()
    r = s.numOfUnplacedFruits([4,2,5], [3,5,4])
    print(r)


