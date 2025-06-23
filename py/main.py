#!/usr/bin/python3

# Unique Binary Search Trees
#
#
# given n nodes, we number them 1..n
# we then ask the q, if i is at the root how many unique BSTs are at its left and
# right subtrees
# example: n = 4
# for n == 1 there is only 1 BST
# for n == 2:
#   we can have i=0 at the root in which its left subtree is n=0 and right subtree is n=1
# for n == 3:
#   we can have i=0: left subtree is n=0, right subtree is n=2
#   i = 1: left subtree is n=1 and right subree is n=1
#   i=2: left subtree is n=2 and right subtree is n=0
# for n==4:
#   i=0, i=1, i=2, i=3. each i has left subtree * right subtree unique BSTs and the total
#   is the sub of the products over all i's
class Solution:
    def numTrees(self, num: int) -> int:
        if num == 1 or num==0:
            return 1
        l: list[int] = [0 for _ in range(0, num+1)]
        l[0] = 1
        l[1] = 1
        
        for n in range(2, num+1):
            for i in range(1, n+1):
                l[n] = l[n] + l[i-1]*l[n-i] 
        
        return l[num]

if __name__ == "__main__":
    s= Solution()
    n = 3
    print(s.numTrees(n))
