#!/usr/bin/python3

# Simple dictionary
# saw a comment mention radix sort so maybe try that for fun later
class Solution:
    def containsDuplicate(self, nums: list[int]) -> bool:
        h: dict[int, int] = {}
        for e in nums:
            if e in h:
                return True
            else:
                h[e] = 1
        return False
if __name__ == "__main__":
    s= Solution()
    r = s.containsDuplicate([1,2,3,4])
    print(r)
