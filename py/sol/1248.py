#!/usr/bin/python3

def find_end(h: dict[int, int], i:int, k:int) -> int:
    if i+k-1 in h:
        return h[i+k-1]
    else:
        return -1
def find_left(prefix: list[int], i: int) -> int:
    left: int = 0
    while i >0:
        if prefix[i-1] == 0:
            left += 1
            i -= 1
        else: break

    return left
 
def find_right(prefix: list[int], j: int) -> int:
    right: int = 0
    while j <len(prefix) -1:
        if prefix[j+1] == 0:
            right += 1
            j += 1
        else: break

    return right
        
class Solution:
    def numberOfSubarrays(self, nums: list[int], k: int) -> int:
        odds: int = 1
        prefix: list[int] = [0] * len(nums)
        h: dict[int, int] = {}
        res: int = 0

        for i in range(0, len(nums)):
            if nums[i] %2 == 1:
                prefix[i] = odds
                h[odds] = i
                odds += 1
        
        for i in range(0, len(prefix)):
            if prefix[i] == 0:
                continue

            start = i
            end = find_end(h, prefix[i], k)
            print(end)
            if end == -1:
                continue
            
            left: int = find_left(prefix, start)
            right:int = find_right(prefix, end)

            res += (left+1)*(right+1) 

        return res

if __name__ == "__main__":
    s= Solution()
    r = s.numberOfSubarrays([2,2,2,1,2,2,1,2,2,2], 2)

    print(r)
