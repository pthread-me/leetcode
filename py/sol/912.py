#! /usr/bin/python3
from typing import Self
from math import ceil

class ListNode:
    def __init__(self, val:int=0, next:Self|None=None):
         self.val:int = val
         self.next:Self|None = next

class Solution:
    def msort(self, nums: list[int])->list[int]:
        if len(nums) == 1:
            return nums
        elif len(nums) == 2:
            if nums[0] > nums[1]:
                nums[0], nums[1] = nums[1], nums[0]

            return nums

        left: list[int] = self.msort(nums[:len(nums)//2])
        right: list[int] = self.msort(nums[len(nums)//2:])

        res: list[int] = [0 for _ in range(len(nums))] 
        p1 = 0
        p2 = 0
        i = 0

        while p1<len(left) and p2<len(right):
            if left[p1] < right[p2]:
                res[i] = left[p1]
                p1 +=1
            else:
                res[i] = right[p2]
                p2 +=1
            
            i+=1


        if p1<len(left):
            for j in range(p1, len(left)):
                res[i] = left[j]
                i+=1
        elif p2 < len(right):
            for j in range(p2, len(right)):
                res[i] = right[j]
                i+=1

        return res


                   
                   

        
       

if __name__ == "__main__":
    S= Solution()
    l = [-2, 3, -5]
    r = S.msort(l)
    
    print(l, r)
