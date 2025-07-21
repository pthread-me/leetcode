#! /usr/bin/python3


# disjoint set
# other solutions just sort and get better times so maybe try that first next time
def get_parent(S: dict[int, tuple[int|None, int]], a: int|None) -> int:
    if a is None:
        exit()
    temp_key = a

    while(S[temp_key][0] is not None):
        temp_key = S[temp_key][0]


    return temp_key

def union(S: dict[int, tuple[int|None, int]], a:int, b:int):
    pa = get_parent(S, a)
    pb = get_parent(S, b)

    if pa == pb:
        return
    else:
        if S[pa][1] > S[pb][1]:
            S[pa] = (None, S[pa][1] + S[pb][1])
            S[pb] = (pa, 1)
        else:
            S[pb] = (None, S[pa][1] + S[pb][1])
            S[pa] = (pb, 1)


class Solution:
    def longestConsecutive(self, nums: list[int]) -> int:
        if len(nums) < 1:
            return 0

        nums = list(set(nums))
        S: dict[int, tuple[int|None, int]] = {}
        
        for e in nums:
            S[e] = (None, 1)

        for e in nums:
            if e-1 in S.keys():
                union(S, e, e-1)
            if e+1 in S.keys():
                union(S, e, e+1)

        
        return max(S.values(), key=lambda x: x[1])[1]

        

if __name__ == "__main__":
    s= Solution()
    r = s.longestConsecutive([0, -1, 1])
    print(r)
