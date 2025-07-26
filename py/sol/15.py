#! /usr/bin/python3

# we can either fix avalue and do 2sum 
# or
# do whats bellow using the facts:
#   1) if there are >3 zeros the [0,0,0] is in res
#   2) is there is 1 zero then we need to find x and -x since x+(-x) +0 = 0
#   3) given a pair of pos values e1,e2 then the sum is zero iff -(e1+e2) exists . Then repeat for negative pairs
class Solution:
    def threeSum(self, nums: list[int]) -> list[list[int]]:
        res: list[list[int]] = []
        zeros = [e for e in nums if e ==0] 
        pos = sorted([e for e in nums if e >0])
        neg = sorted([e for e in nums if e <0])

        pos_set: set[int] = set(pos)
        neg_set: set[int] = set(neg)
        
        pos_pairs: set[tuple[int, int]] = set([(pos[i], pos[j]) for i in range(0, len(pos)-1) for j in range(i+1, len(pos))])
        neg_pairs: set[tuple[int, int]] = set([(neg[i], neg[j]) for i in range(0, len(neg)-1) for j in range(i+1, len(neg))])
         

        if len(zeros) > 2:
            res.append([0,0,0])
        if len(zeros)> 0:
            for e in pos_set:
                if -1*e in neg_set:
                    res.append([e,0,-1*e])


        for e in pos_pairs:
            if -(e[0]+e[1]) in neg_set:
                res.append([e[0], e[1], -(e[0]+ e[1])])


        for e in neg_pairs:
            if -(e[0]+e[1]) in pos_set:
                res.append([e[0], e[1], -(e[0]+ e[1])])

        return res 


if __name__ == "__main__":
    s= Solution()
    r = s.threeSum([-1,0,1,2,-1,-4,-2,-3,3,0,4])
    print(r)
