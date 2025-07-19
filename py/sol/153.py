#! /usr/bin/python3

# We know that the array is already sorted, so we want to find the exact location where
# the ascending order condition no longer holds, that tells us where the array
# exactly starts -> the min element
class Solution:
    def findMin(self, nums: list[int]) -> int:
        if len(nums) <3:
            return min(nums)

        mid: int =  len(nums)//2
        if nums[mid+1]<nums[mid]:
            return nums[mid+1]
        elif nums[mid] < nums[mid-1] and nums[mid] < nums[mid+1]:
            return nums[mid]
        else: 
            if nums[mid+1] > nums[len(nums)-1]:
                return self.findMin(nums[mid+1:])
            else:
                return self.findMin(nums[0:mid])

if __name__ == "__main__":
    s= Solution()
    r = s.findMin([0,1,2])

    print(r)
