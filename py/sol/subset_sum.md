# Subset Sum

## Description:

Given a target t and a list nums we want to find the number of subsets in nums that sum up to t

## DP approach:
for every element e in nums, we can represent a number n if there exists a combination of elements in nums
that already sum up to n-e, else adding e to any other comb will not result in n.

The general approach is as follows:
1. We iterativley the number of ways to find all n's from \[0,n\] 
2. for every e in nums, we check if there are comb that sum up to n-e, if so adding e to them results in n, thus
    increasing the number of ways we can represent n by the number of said comb

example:

nums = 1, 1, 1, 2
target is 4

first the number of ways we can represent 0 is 1, so the dp is
    '0 '1 '2 '3 '4
dp = 1, 0, 0, 0, 0

for nums\[0\] = 1 to rep 4 we need to add it to a comb that sums to 3, no such comb exist to '4 remains as 0
same for '3 '2. at '1 adding 1 to the combs rep '0 we get a sum of 1 so '1 = 1

dp = 1, 1, 0, 0, 0

at nums\[1\] = 1, we still cant rep '4 '3. at '2 there is already one comb that sums up to '1 so adding 1 to it gives 2, then '2 += '1 = 1
same for '1 there is a comb that sums to '0 so '1 += '0 = 2

dp = 1, 2, 1, 0, 0

repeat for all e in nums and dp\[-1\] is the numb of ways to sum up to '4 == t


see 494.py for code
