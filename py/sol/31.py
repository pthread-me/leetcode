#! /usr/bin/python3

# to find the next permutation:
#   we want to find the first decreasing value from the right and swap it
#   with the smallest value that it larger than it to the right
#
#   We then reverse the values to the left of the first decreasing value

#ex:
#   0,6,5,1,0
# i = 0 -> index
# j the largest val to its right is 1 so j=3
# this gives:
#   1,6,5,0,0
# but now all elements to i's right is in lex increasing we want too turn it to dec so rev
class Solution:
    def nextPermutation(self, nums: list[int]) -> None:
        if len(nums)<2:
            return
        i:int = len(nums)-1

        # find the first dec value from the left 
        while i>0:
            if nums[i] <= nums[i-1]:
                i-=1
            else:
                i-=1
                break
       
        # find the min value starting from i that is greater than i
        j:int = i+1
        while j<len(nums):
            if nums[j] <= nums[i]:
                break
            j+=1

        j-=1

        # swap i and j
        temp = nums[j]
        nums[j] = nums[i]
        nums[i] = temp
        

        # once we swap we reverse all elements after i
        if i<j:
            i+=1
        for k in range(0, (len(nums)-i)//2):
            temp = nums[i+k]
            nums[i+k] = nums[len(nums)-1-k]
            nums[len(nums)-1-k] = temp


if __name__ == "__main__":
    S= Solution()
    l = [0,6,5,1,1]
    r = S.nextPermutation(l)
    print(l)
