#!/usr/bin/python3


class Solution:
    def groupAnagrams(self, strs: list[str]) -> list[list[str]]:
        map: dict[str, list[str]] = {}

        for e in strs:
            key = "".join(sorted(e))
            map[key] = map.get(key, []) + [e]
        
        
        res: list[list[str]] = []
        for k in map:
            res.append((map[k]))
        
        return res




if __name__ == "__main__":
    s= Solution()
    r = s.groupAnagrams(["eat","tea","tan","ate","nat","bat"])
    print(r)
