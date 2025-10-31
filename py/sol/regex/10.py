#! /usr/bin/python3

# We use dynamic programming to decide if the current pattern passes or fails
# for non * p[i], p must consume s[j] 
#   this means that p[i-1] must pass for s[j-1]
# if p[i] is a *, p can either not consume s[j], but it also couldve consumed s[j-1]
#   this means we can ignore p[i] (by looking at A[i-1][j] to see if p[i-1] consumed s[j])
#   if we dont ignore it, to consume it either p[i-1] or s[i] consumed s[j-1]

# to consume a char we need to either be equal to it or be .

# we also do some preprocessing,where for all p[0..i] where p[i] is the first non * character
# all the starting patterns can be ignored so we set A[i][0] = True

# think of A's first row as matching against . 
# while its first column is matching a $ character 

class Solution:
    def isMatch(self, s: str, pattern: str) -> bool:
        def cmp(p:str, s:str):
            return (p==".") or (p == s)

        # Setting up the pattern to include the * info
        p: list[tuple[str, bool]] = []
        i = 0
        while i<len(pattern):
            if i+1<len(pattern) and pattern[i+1] == "*":
                p.append((pattern[i], True))
                i += 2
            else:
                p.append((pattern[i], False))
                i += 1
        


        A: list[list[bool]] = [[True if i==0 and j==0 else False for j in range(0, len(s)+1)] 
                               for i in range(0, len(p)+1)]
        
        # preproessing the first k * chars in p setting their A[i][0] = True
        i = 0
        while i<len(p) and p[i][1]:
            A[i+1][0] = True
            i += 1

        # main loop
        for i in range(1, len(A)):
            for j in range(1, len(A[i])):
                if p[i-1][1] == True:
                    A[i][j] = (A[i-1][j]) or (cmp(p[i-1][0], s[j-1]) and (A[i-1][j-1] or A[i][j-1]))
                else:
                    A[i][j] = cmp(p[i-1][0], s[j-1]) and A[i-1][j-1]
        
        for r in A:
            print(r)
        return A[-1][-1]

        
if __name__ == "__main__":
    S = Solution()
    s = "a"
    p = "ab*a"
    r = S.isMatch(s, p)
    print(r)
