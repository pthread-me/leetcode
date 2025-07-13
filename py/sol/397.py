#!/usr/bin/python3

# we always want to divide:
# when even there is nothing we can do but divide
# when odd we have a choice between dividing odd-1 or odd+1
# we want to choose one that guarentees the step after the division (so steps would be: add->div->add or div)
# we want the 3rd step to be div, so we look further down the chain of operations and choose +/- that makes 
# the 3rd op be a div
class Solution:
    def integerReplacement(self, n: int) -> int:
        i = 0
        while not n == 1:
            if n%2 == 0:
                n = n//2
            else:
                if (n-1)//2  %2 == 0 or (n-1)//2 == 1:
                    n = n-1
                else:
                    n = n+1
            i = i+1

        return i
if __name__ == "__main__":
    s= Solution()
    r = s.integerReplacement(5)
    print(r)
