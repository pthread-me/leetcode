#! /usr/bin/python3

# An array of initial gaps and a windowed walk on the gaps we can combine (thus their sum)
# if k=1 then we can combine 2 gaps by moving 1 block. Then the size of the window is k+1 (so [0,k] )
class Solution:
    def maxFreeTime(self, eventTime: int, k: int, startTime: list[int], endTime: list[int]) -> int:
        gap: list[int] = []

        gap.append(startTime[0])
        for i in range(0, len(endTime)-1):
            gap.append(startTime[i+1] - endTime[i])
        gap.append(eventTime - endTime[-1])
        if k-1 >= len(gap):
            return sum(gap)

        i = 0
        j = k
        window = sum(gap[i:j+1])
        m = window 

        while j<len(gap)-1:
            window = window - gap[i] + gap[j+1]   
            #print(window)
            i += 1
            j += 1
             
            m = max(window, m)

        return m
        

if __name__ == "__main__":    
    S = Solution()
    r = S.maxFreeTime(21, 1, [7,10,16], [10,14,18])
    print(r)
