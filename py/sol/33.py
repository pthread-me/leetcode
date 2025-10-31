#! /usr/bin/python3

# Binary search on rotated array


class Solution:
    def search(self, nums: list[int], target: int) -> int:
        i:int = 0
        j:int = len(nums)-1


        while i<=j:
            mid = (j-i)//2 + i
            print(i,j,mid)
            if nums[mid] == target:
                return mid
            elif nums[i] == target:
                return i
            elif nums[j] == target:
                return j


            if nums[i] < nums[mid]:
                if nums[i]<= target < nums[mid]:
                    j=mid-1
                else:
                    i=mid+1
            else:
                if nums[mid] < target <= nums[j]:
                    i = mid+1
                else:
                    j= mid-1
        
        return -1
if __name__ == "__main__":
    S= Solution()
    l = [4,3,2,1]
    r = S.search(l, 1)
    print(r)
