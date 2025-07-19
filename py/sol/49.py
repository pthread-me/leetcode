#!/usr/bin/python3

# My solution sorts the strs and uses the sorted version as a key
# we can instead have a hash function that uses the (ascii value - 97) times the
# occurence of each character as a key. example: ate -> 1*(97-97) + 1*(e-97) + 1*(t-97)
class Solution:
    def groupAnagrams(self, strs: list[str]) -> list[list[str]]:
        pairs: list[list[str]] = list(map(lambda e:[e, "".join(sorted(e))], strs))
        
        h: dict[str, list[str]] = {}

        for e in pairs:
            key = e[1]
            if key in h:
                h[key].append(e[0])
            else:
                h[key] = [e[0]]

        res: list[list[str]] = []
        for l in h.values():
            res.append(l)

        return res

if __name__ == "__main__":
    s= Solution()
    r = s.groupAnagrams(["eat","tea","tan","ate","nat","bat"])
    print(r)
