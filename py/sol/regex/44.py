#! /usr/bin/python3

# A copy of 10.py with input modification:
# can be done quicker but this works

class Solution:
    def isMatch(self, s: str, pattern: str) -> bool:
        def cmp(p:str, s:str):
            return (p==".") or (p == s)

        # Setting up the pattern to include the * info
        p: list[tuple[str, bool]] = []
        i = 0
        while i<len(pattern):
            if pattern[i] == "?":
                p.append((".", False))
            elif pattern[i] == "*":
                p.append((".", True))
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
