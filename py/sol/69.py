class Solution:
    def __init__(self):
        squares = []
        for i in range(1, (2**16)):
            squares.append(i*i)
        self.squares = squares
    
    def bi_search(self, x: int, i:int, j:int):
        mid: int = int (i + (j-i)/2)
        print(f'index: {mid}\t val: {self.squares[mid]}')
        if mid == 0:
            return mid

        if self.squares[mid] == x:
            return mid
        elif self.squares[mid]>x and self.squares[mid-1] < x:
            return mid-1
        elif self.squares[mid]<x and mid<len(self.squares)-1 and self.squares[mid+1]>x:
            return mid
        elif self.squares[mid] < x:
            return self.bi_search(x, mid, j)
        else:
            return self.bi_search(x, i, mid)



    def mySqrt(self, x: int) -> int:
        if x < 1:
            return 0 
        elem = self.bi_search(x, 0, len(self.squares)-1)
        return elem +1


if __name__ ==  "__main__":
    s = Solution()
    n = 0
    print(s.mySqrt(n))
