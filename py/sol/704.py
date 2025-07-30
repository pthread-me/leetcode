#! /usr/bin/python3

# binary search
class Solution:
    def search(self, nums: list[int], target: int) -> int:
        if len(nums) < 1:
            return -1
       
        i: int = 0
        j:int = len(nums) -1

        while i <= j:
            mid: int = i + (j-i)//2
            if nums[mid] < target:
                i = mid +1
            elif nums[mid] > target:
                j = mid-1
            else:
                return mid

        return -1

if __name__ == "__main__":    
    S = Solution()
    r = S.search([2, 5], 5)
    print(r)
