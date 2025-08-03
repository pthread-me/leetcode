#! /usr/bin/python3


# We keep a hashtable of the chars in s1 with a counter, then perform a windowed walk over
# s2 where the size of the window is == s1. Every iter we increase the value of s2[i] since it leaves
# the window and decrease the value of s2[j], once all values == 0, then a permutation is found.

class Solution:
    def checkInclusion(self, s1: str, s2: str) -> bool:
        if len(s1) > len(s2):
            return False

        table: dict[str, int] = {}
        for e in s1:
            table[e] = table.get(e, 0) + 1


        for i in range(0, len(s1)):
            if s2[i] in table:
                table[s2[i]] = table[s2[i]] -1
        
        if all([table[e] == 0 for e in table]):
                return True

        i = 0
        j = len(s1)

        while j<len(s2):
            if s2[i] == s2[j]:
                i += 1
                j += 1
            else:
                if s2[i] in table:
                    table[s2[i]] = table[s2[i]] + 1
                if s2[j] in table:
                    table[s2[j]] = table[s2[j]] -1

                if all([table[e] == 0 for e in table]):
                    return True
                i += 1
                j += 1
        return False
            

if __name__ == "__main__":
    s = Solution()
    r = s.checkInclusion("ab", "eidb19aoooba")
    print(r)
