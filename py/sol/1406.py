#! /usr/bin/python3

# Similar to stonegame 2, we can construct a solution that explores all
# possible recursion paths and cache the best solution for each index.

# This give a TLE since we are doing more than what is necessary, given that the
# step length does not change; instead of a top down approach we can start from the end (bottom up)
# in which the solution for an index i is the max of sum(from i to j in stoneValue) - A[j+1]
class Solution:

    def SimilarToStoneGameII(self, stoneValue: list[int]) -> str:
        def T(i:int)-> None:
            first = stoneValue[i] - A[i+1]
            second = stoneValue[i] + stoneValue[i+1] - A[i+2]
            third = stoneValue[i] + stoneValue[i+1] + stoneValue[i+2] - A[i+3]
        
            A[i] = max(first, second, third)
            


        A: list[int] = [0 for _ in stoneValue] 
        for i in range(1, 4):
            if len(A) -i < 0:
                break

            index = len(A) -i
            A[len(A)-i] = max([sum(stoneValue[index:index+j]) for j in range(1, i+1)])
        

        # initial setup of the last 3 indecies
        A[-1] = stoneValue[-1]
        if len(A)>1:
            index = len(A)-2
            print(index)
            A[index] = max(stoneValue[index] - A[index +1], stoneValue[index] + stoneValue[index +1])
        if len(A)>2:
            index = len(A) -3
            A[index] = max(stoneValue[index] - A[index+1], 
                           stoneValue[index]+stoneValue[index+1]-A[index+2], 
                           stoneValue[index]+stoneValue[index +1] + stoneValue[index +2])

        # filling up the remaining [0: len-4]
        for i in range(len(A)-4, -1, -1):
            T(i)


        alice:int = A[0]
        print(A)
        if alice > 0:
            return "Alice"
        elif alice == 0:
            return "Tie"
        else:
            return "Bob"



    def stoneGameIII(self, stoneValue: list[int]) -> str:
        def T(i:int)-> None:
            first = stoneValue[i] - A[i+1]
            second = stoneValue[i] + stoneValue[i+1] - A[i+2]
            third = stoneValue[i] + stoneValue[i+1] + stoneValue[i+2] - A[i+3]
        
            A[i] = max(first, second, third)
            


        A: list[int] = [0 for _ in stoneValue] 
        for i in range(1, 4):
            if len(A) -i < 0:
                break

            index = len(A) -i
            A[len(A)-i] = max([sum(stoneValue[index:index+j]) for j in range(1, i+1)])
        

        # initial setup of the last 3 indecies
        A[-1] = stoneValue[-1]
        if len(A)>1:
            index = len(A)-2
            print(index)
            A[index] = max(stoneValue[index] - A[index +1], stoneValue[index] + stoneValue[index +1])
        if len(A)>2:
            index = len(A) -3
            A[index] = max(stoneValue[index] - A[index+1], 
                           stoneValue[index]+stoneValue[index+1]-A[index+2], 
                           stoneValue[index]+stoneValue[index +1] + stoneValue[index +2])

        # filling up the remaining [0: len-4]
        for i in range(len(A)-4, -1, -1):
            T(i)


        alice:int = A[0]
        print(A)
        if alice > 0:
            return "Alice"
        elif alice == 0:
            return "Tie"
        else:
            return "Bob"



if __name__ == "__main__":
    s = Solution()
    r = s.stoneGameIII([-3,4,-7,7,-8,-4,-12,-8,11,-11,-3,-1,13,14,0,9,-13,-17,-6,10,15,-1,7])
    print(r)
