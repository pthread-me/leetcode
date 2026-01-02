#! /usr/bin/python3

class Solution:
    def generate(self, numRows: int) -> list[list[int]]:
        if numRows < 1:
            return []
        elif numRows == 1:
            return [[1]]

        res: list[list[int]] = [[1]] 

        for r in range(1, numRows):
            prev: list[int] = res[r-1]
            cur: list[int] = [1] + ([0]* (len(prev))) 

            for i in range(0, len(prev)-1):
                cur[i+1] = prev[i] + prev[i+1]
            
            cur[-1] = 1
            res.append(cur)

        return res

if __name__ == "__main__":
    S = Solution()
    s = 5
    r = S.generate(s)
    print(r)
