#! /usr/bin/python3
#from typing import Self

class Solution:
    def plusOne(self, digits: list[int]) -> list[int]:
        digits = digits[::-1]
        i:int = 0

        while True:
            if i>=len(digits):
                digits.append(1)
                break
            elif digits[i] == 9:
                digits[i] = 0
                i+=1
            else:
                digits[i] +=1
                break

        return digits[::-1]

if __name__ == "__main__":
    s = Solution()
    l = [9]
    r = s.plusOne(l)
    print(r)

    
