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
        self.tree[v] = self.tree[2*v+1] + self.tree[2*v+2]
        
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
        if i>=len(tree.src):
            return

        tree.src[i] = val
        tree.__update__(0, 0, len(src)-1, i, val)

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
         
if __name__ == "__main__":
    src: list[int] = [-8261,2300,-1429,6274,9650,-3267,1414,-8102,6251,-5979,-5291,-4616,-4703]
    tree = SegmentTree(src)
    print(f"sum from [0,8] is {tree.query(0, 0,8,0,len(src)-1)}")


