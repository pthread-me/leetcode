#! /usr/bin/python3

# We keep a hashset of the seen characters and use a two pointer walk.
# if j encounters a char not in the set then we add it other wise there is a repeated
# char between i and j, so we skip over the characters until we find the index x of the repeated char
# and set i = x+1. and continue
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        if len(s)<2:
            return len(s)

        table: set[str] = set()
        i = 0
        j = 1
        
        table.add(s[i])
        longest = 1

        while j<len(s):
            print(table, i, j)
            if s[j] in table:
                # remove all elems before the repeated char
                while (not s[i] == s[j]):
                    table.remove(s[i])
                    i += 1

                # skip over the repeated character on the left
                i += 1
            else:
                table.add(s[j])
            j+=1
            
            # we check after incrementing j, because we need the inclusive range s[i..j]
            longest = max(longest, j-i)

        return longest


if __name__ == "__main__":
    s = Solution()
    r = s.lengthOfLongestSubstring("abcabcbb")
    print(r)
