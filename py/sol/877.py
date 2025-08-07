#! /usr/bin/python3



# Alice always wins:
# We can calculate the max in each turn, then since alice goes first she can choose the
# set of turns that return the max

class Solution:
    def stoneGame(self, _: list[int]) -> bool:
        return True


    def approach_to_get_to(self, piles: list[int]):
        p1: int = 0
        p2: int = 0

        i = 0
        j = len(piles) -1

        turns: list[int] = []
        while i<=j:
            if piles[i]>=piles[j]:
                turns.append(piles[i])
                i+=1
            else:
                turns.append(piles[j])
                j-=1

        for i in range(0, len(piles), 2):
            p1 += turns[i]
            p2 += turns[i+1]
        
        print(turns)
        print(p1, p2)


if __name__ == "__main__":
    s = Solution()
    r = s.stoneGame([3,2,10,4])
    print(r)
