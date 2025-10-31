#! /usr/bin/python3

class Solution:
    def maxAscendingSum(self, nums: list[int]) -> int:
        sum = nums[0]
        max_sum = nums[0]
        for i in range(1, len(nums)):
            if nums[i-1] < nums[i]:
                sum += nums[i]
            else:
                max_sum = max(max_sum, sum) 
                sum = nums[i]

        return max(sum, max_sum)


if __name__ == "__main__":
    s = Solution();
    r = s.maxAscendingSum([10,20,30,5,10,50])
    print(r)
