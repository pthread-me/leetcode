#! /usr/bin/python3
#from typing import Self

class Solution:
    def combinationSum2(self, candidates: list[int], target: int) -> list[list[int]]:
        res: list[list[int]] = []
        candidates.sort()

        def backtrack(temp: list[int], sum:int, offset:int):
            if sum == target and temp not in res:
                res.append(temp[:])
            elif sum < target:
                check: set[int] = set()
                for i in range(offset, len(candidates)):
                    if candidates[i] not in check:
                        check.add(candidates[i])
                        temp.append(candidates[i])
                        backtrack(temp, sum+candidates[i], i+1)
                        _ = temp.pop()
            else:
                return

        backtrack([], 0, 0)
        return res

if __name__ == "__main__":
    s = Solution()
    l = [10,1,2,7,6,1,5]
    r = s.combinationSum2(l, 8)
    print(r)

    
