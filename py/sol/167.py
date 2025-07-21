#! /usr/bin/python3

# two pointer classic
class Solution:
    def twoSum(self, numbers: list[int], target: int) -> list[int]:
        i = 0
        j = len(numbers) -1

        while i < j:
            s = numbers[i] + numbers[j]
            if s == target:
                return [i+1, j+1]
            elif s < target:
                i+=1
            else:
                j-=1

        # unreachible
        return [-1, -1]
                
if __name__ == "__main__":
    s= Solution()
    r = s.twoSum([2, 3, 4], 6)
    print(r)
