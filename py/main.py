#! /usr/bin/python3


def check_win(s:str) -> bool:
    for e in s:
        if e == "0":
            return True
    return False

class Solution:
    def canReach(self, s: str, minJump: int, maxJump: int) -> bool:
        if len(s) <= 1:
            return True
        if s[-1] == "1":
            return False

        start = minJump
        end = maxJump

        while end < len(s)-1:
            print(s[start: end+1])
            if check_win(s[start: end+1]) == False:
                return False

            while not s[start] == "0" and start <= end:
                start +=1

            if end>= len(s):
                end = len(s) -1
            else:
                while not s[end] == "0" and end>=start:
                    end -=1

            start += minJump
            end += maxJump
    
        return check_win(s[start: end+1])
        


if __name__ == "__main__":    
    S = Solution()
    input: str = open("input.txt").read().strip()
    
    r = S.canReach("00111010", 3, 5)
    print(r)
