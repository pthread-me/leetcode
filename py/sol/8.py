#! /usr/bin/python3


# simple loop
class Solution:
    def myAtoi(self, s: str) -> int:
        s = s.lstrip(" ") 
        negative: bool = False
        val:int = 0

        if len(s)<=0:
            return 0
        elif s[0] == "-":
            s = s[1:]
            negative = True
        elif s[0] == "+":
            s = s[1:]
        
        s = s.lstrip("0")
        for e in s:
            if ord(e) < 48 or ord(e) > 57:
                break
            val = val*10 + int(e)


        if negative and val>pow(2, 31):
            val = pow(2, 31)
        elif (not negative) and val>pow(2, 31)-1:
            val = pow(2, 31) -1
           
        return (val*-1 if negative else val)



if __name__ == "__main__":
    s = Solution()
    r = s.myAtoi("-0012a42")
    print(r)
