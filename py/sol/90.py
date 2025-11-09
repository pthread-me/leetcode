#! /usr/bin/python3
#from typing import Self

# Starting with the permutation solution (q46)
# we again have elements compete for possitions which we then swap to and append
# ex:
#   [1,2,3]
#   we start with res =  []
#   then for i = 0 we swap and take nums[:0] 
#   A) [1,2,3] -> [1,2,3] = [1]
#   B) [1,2,3] -> [2,1,3] = [2]
#   C) [1,2,3] -> [3,2,1] = [3]
#
#   In the second recursive level i = 1 on A:
#       [1,2,3] -> [1,2,3] = [1,2]
#       [1,2,3] -> [1,3,2] = [1,3]
#
#   In the second recursive level i=1 on B:
#       [2,1,3] -> [2,1,3] = [2,1]
#       [2,1,3] -> [2,3,1] = [2,3]
#
#
#   Observe the [1,2] == [2,1] when dealing with combinations, so in the second level
#   on the second element (B) we want to ignore the first result (of the swap) and only start adding from the second
#   onwards. similarly with the 3rd.
#
#   So we have an sp offset which dicates the index of the elements where the swapping begins
class Solution:
    def subsetsWithDup(self, nums: list[int]) -> list[list[int]]:
        res: list[list[int]] = [] 
        nums.sort()

        def sub(i:int, sp: int):
            if nums[:i] in res:
                return
            res.append(nums[:i])
            
            for j in range(i+sp, len(nums)):
                nums[i], nums[j] = nums[j], nums[i]
                sub(i+1, sp)
                sp += 1
                nums[i], nums[j] = nums[j], nums[i]

        sub(0, 0)
        return res

        
if __name__ == "__main__":
    s = Solution()
    l = [4,1,0, 2]
    r = s.subsets(l)
    print(r)

    
