#! /usr/bin/python3

from math import floor

# if x,y have the same parity then bob wins, else alice wins
# so we just count the number of pairs between 1..m and 1..n where x,y have diff parity

class Solution:
    def flowerGame(self, n: int, m: int) -> int:
        if n<1 or m<1:
            return 0

        def parity(i:int) -> tuple[int, int]:
            even:int = floor(i/2)
            return (even, i-even)
        

        n_e, n_o = parity(n)
        m_e, m_o = parity(m)

        return (n_e * m_o) + (n_o * m_e)

if __name__ == "__main__":
    S = Solution()
    r = S.flowerGame(1,1)
    print(r)
