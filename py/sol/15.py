#! /usr/bin/python3

# we use two sum while ancoring one value k, and skiping duplicate values

class Solution:
    def threeSum(self, nums: list[int]) -> list[list[int]]:
        nums.sort()
        res: list[list[int]] = []


        for k in range(0, len(nums)-2):
            if k>0 and nums[k] == nums[k-1]:
                continue
            target: int = -nums[k]

            i:int = k+1
            j:int = len(nums)-1
            
            while i<j:
                if nums[i] + nums[j] < target:
                    i+=1
                elif nums[i] + nums[j] > target:
                    j-=1
                else:
                    sol = [nums[k], nums[i], nums[j]]
                    res.append(sol)
                    i+=1
                    while i<j and nums[i] == nums[i-1]:
                        i+=1
        
        return res

if __name__ == "__main__":
    S = Solution()
    n = [-1,0,1,2,-1,-4]
    r = S.threeSum(n)
    print(r)

     
