#! /usr/bin/python3

def trivial(s: list[str], i: int, tip: int) -> int:
    if i<0 or i>=len(s):
        return 0

    b:int = tip
    while i-b >=0 and i+b<len(s):
        if s[i-b] == s[i+b]:
            b+=1
        else:
            break

    print(f"Trivial on i:{i}, starting from: {tip}")
    return b-1



class Solution:
    def longestPalindrome(self, input: str)-> str:
        s: list[str] = list(input)
        odd = True
        
        if len(s) <= 1:
            return input
        
        elif len(s) % 2== 0:
            odd = False
            new_s = ["#"]
            for e in s:
                new_s.append(e)
                new_s.append("#")
            s = new_s

        h = [1] + ([0] * (len(s)-1))
        (l,r) = (0,1)

        

        for i in range(1, len(s)):
            if r >= len(s):
                break
            if i>=r:
                h[i] = trivial(s, i, 0)*2 + 1
                (l, r) = (i-(h[i]-1)//2, i+(h[i]-1)//2)
            else:
                mirror: int = h[l+(r-i)]
                if mirror+i >r:
                    print(f"i:{i}, Out")
                    h[i] = (mirror+i) -r
                elif mirror+i < r:
                    print(f"i:{i}, In")
                    h[i] = mirror
                else:
                    h[i] = trivial(s, i, mirror)*2 + 1
                    (l, r) = (i-h[i], i+h[i]) 

            print(f"i:{i}, h:{h}")

        
        if odd:
            val = (max(h)-1)//2
        else:
            val = (max(h)-1)//4

        index:int = h.index(max(h))
        print(val, index)
        
        return input[index-val:index+val+1]


if __name__ == "__main__":    
    S = Solution()
    r = S.longestPalindrome("abababcd")
    print(r)
