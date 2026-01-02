#!/usr/bin/python

class Solution:
    def threeSumClosest(self, nums: list[int], target: int) -> int:
        nums.sort()
        res: float = float('inf')
        res_diff = float('inf')

        for i in range(len(nums)-2):
            l,r = i+1, len(nums)-1
            while l<r:
                if abs(target - (nums[i]+nums[l]+nums[r])) < res_diff:
                    res = nums[i]+nums[l]+nums[r]
                    res_diff = abs(target - (nums[i]+nums[l]+nums[r]))

                if nums[i]+nums[l]+nums[r] < target:
                    l+=1
                else:
                    r-=1

        return int(res)

            

        


if __name__ == "__main__":
    s = Solution()
    n = [4,0,5,-5,3,3,0,-4,-5]
    t = -2

    r = s.threeSumClosest(n,t)
    print(r)

