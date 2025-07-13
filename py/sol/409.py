#!/usr/bin/python3


class Solution:
    def longestPalindrome(self, s: str) -> int:
        table: dict[str, int] = {}
        flag: bool = True
        result = 0

        for e in s:
            if e in table:
                table[e] = table[e] + 1
            else:
                table[e] = 1
        
        for key in table.keys():
            if flag == True and table[key]%2 == 1:
                result = result + table[key]
                flag = False
            else:
                result = result + table[key] - (table[key] % 2)

        print(table)
        return result
                

if __name__ == "__main__":
    s= Solution()
    r = s.longestPalindrome("abccccdd")
    print(r)
