#! /usr/bin/python3

# solution is simple, kind of like a prefix sum but for products
# if there exists a 0 then all of res is 0 except possibly res[index of 0 in nums]
# to get res[i], we know that res[i-1] is the product of all (including nums[i] except nums[i-1])
# so we just multiply back nums[i-1] and remove (divide by) nums[i]

def prod_except_i(nums:list[int], i: int):
    res: int = 1
    for j in range(0, len(nums)):
        if not j == i:
            res *= nums[j]
    return res

class Solution:
    def productExceptSelf(self, nums: list[int]) -> list[int]:
        res: list[int] = [0] * len(nums)
        
        if 0 in nums:
            res[nums.index(0)] = prod_except_i(nums, nums.index(0))
            return res

        res[0] = prod_except_i(nums, 0)
        for i in range(1, len(nums)):
            res[i] = (res[i-1] * nums[i-1]) // nums[i]

        return res

if __name__ == "__main__":
    s= Solution()
    r = s.productExceptSelf([-1,1,0,-3,3])

    print(r)
