#! /usr/bin/python3

# The question wants the first k elements to be the unique one's and to return 
# the NO. of unique elements:
# we can do this by removing dupes, OR, replacing the first k elements with the unique e's 
# which is what im doing here
class Solution:
    def removeDuplicates(self, nums: list[int]) -> int:
        if len(nums)<2:
            return len(nums)
        
        i:int = 0
        j:int = 1
        res:int = 1

        while j<len(nums):
            if nums[i] == nums[j]:
                j += 1
            else:
                nums[i+1] = nums[j]
                i += 1
                j += 1
                res += 1 
                
        return res



if __name__ == "__main__":
    S= Solution()
    l = [1,1,2,2,5,6,7,8,8]
    r = S.removeDuplicates(l)
    print(l)
    print(r)
