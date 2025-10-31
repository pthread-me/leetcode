#! /usr/bin/python3


# nlogn + 3n, to sort then a walk is n with a 2n to search
class Solution:
    def twoSum(self, nums: list[int], target: int) -> list[int]:
        if len(nums) <3:
            return [0,1] if sum(nums) == target else []
        
        A = sorted(nums)
        i: int = 0
        j:int = len(nums)-1

        while i<j:
            if A[i] + A[j] == target:
                if A[i] == A[j]:
                    x = nums.index(A[i])
                    y = nums.index(A[j], x+1)
                else:
                    x = nums.index(A[i])
                    y = nums.index(A[j])

                return [x,y]
            elif A[i] + A[j] < target:
                i+=1
            else:
                j-=1

        return []



if __name__ == "__main__":
    S= Solution()
    l = [3,3]
    t = 6
    r = S.twoSum(l, t)
    print(r)
