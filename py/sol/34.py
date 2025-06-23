class Solution:
    
    def bi_search(self, nums:list[int], x: int, i:int, j:int, res:list[int]) -> list[int]:
        if i>j:
            return res
        mid:int = i + int((j-i)/2)
        print(mid)
        if nums[mid] == x: 
            start = mid
            end = mid

            if mid==0:
                start = mid
            else:
                start = mid
                while start >0 and nums[start-1]==x:
                    start = start-1
            if mid == len(nums)-1:
                end = mid
            else:
                while end<len(nums)-1 and nums[end+1] == x:
                    end = end+1
            return [start, end]

        elif nums[mid] > x:
            return self.bi_search(nums, x, i, mid-1, res)
        else:
            return self.bi_search(nums, x, mid+1, j, res)

    def searchRange(self, nums: list[int], target: int) -> list[int]:
       res = [-1, -1]
       return self.bi_search(nums , target, 0, len(nums)-1, res)

if __name__ == "__main__":
    s = Solution()
    l = [5,7,7,8,8,10]
    n = 6
    print(s.searchRange(l, n))
