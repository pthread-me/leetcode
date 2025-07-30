#! /usr/bin/python3

        

# binary search on the columns first then on the rows
class Solution:
    def findRow(self, matrix: list[list[int]], target:int) -> int:
        i:int = 0
        j:int = len(matrix) -1
        while i<=j:
            mid:int = i+ (j-i)//2
            if matrix[mid][-1] >= target and matrix[mid][0] <= target:
                return mid
            elif matrix[mid][-1] < target:
                i = mid+1
            else:
                j = mid-1

        return -1
    def searchMatrix(self, matrix: list[list[int]], target: int) -> bool:
        if len(matrix) == 1:
            row = 0
        else:
            row = self.findRow(matrix, target)

        if row < 0:
            return False

        nums: list[int] = matrix[row] 
        if len(nums) < 1:
            return False
       
        i: int = 0
        j:int = len(nums) -1

        while i <= j:
            mid: int = i + (j-i)//2
            if nums[mid] < target:
                i = mid +1
            elif nums[mid] > target:
                j = mid-1
            else:
                return True

        return False


if __name__ == "__main__":    
    S = Solution()
    r = S.searchMatrix([[0,1],[2, 5]], 5)
    print(r)
