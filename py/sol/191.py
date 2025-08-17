#! /usr/bin/python3


# Brian Kernighan’s Algorithm: Count set bits in a number


class Solution:
    def hammingWeight(self, n: int) -> int:
        count = 0
        while n>0:
            n = n&(n-1)
            count += 1 
        return count


if __name__ == "__main__":
    s = Solution()
    r = s.hammingWeight(22)
    print(r)
