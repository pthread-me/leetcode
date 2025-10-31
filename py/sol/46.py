#! /usr/bin/python3
#from typing import Self
        
        

class Solution2:
    def permute(self, nums: list[int]) -> list[list[int]]:
        res: list[list[int]] = []

        def backtrack(level: int, choice: list[int]):
            if level == len(choice):
                return

            if choice not in res:
                res.append(choice)
            backtrack(level+1, choice)
            for i in range(level+1, len(choice)):
                next_choice = choice.copy()
                temp = next_choice[level]
                next_choice[level] = next_choice[i]
                next_choice[i] = temp

                if next_choice not in res:
                    res.append(next_choice)
                    backtrack(level+1, next_choice)
        
        backtrack(0, nums)
        return res

class Solution:
    def permute(self, nums: list[int]) -> list[list[int]]:
        res: list[list[int]] = []

        def per(i:int):
            if i == len(nums):
                res.append(nums.copy())

            for j in range(i, len(nums)):
                nums[i], nums[j] = nums[j], nums[i]
                per(i+1)
                nums[i], nums[j] = nums[j], nums[i]
        
        per(0)
        return res

if __name__ == "__main__":
    s = Solution()
    l = [5,4,6,2]
    r = s.permute(l)
    print(r)

    
