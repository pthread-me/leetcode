#! /usr/bin/python3


# We keep a counter for all the characters seen
# at every iteration, we get the maximum char's count (most) and the sum of all other chars
# in the interval (k_space). while k_space is less than k, we can extend the interval.

# When k_space is greater than or equal to k, we need to shift the left pointer until either:
#   1) The sum of the chars not == to most is <k
#               OR
#   2) The char with most count is now less than k so it can be "replaced"

# At each iteration we get the size of the interval which will tell us the overall maxsize
class Solution:
    def characterReplacement(self, s: str, k: int) -> int:
        if len(s)<= k or len(s)<2:
            return len(s)
        
        table: dict[str, int] = {}
        i = 0
        j = 1
        
        table[s[i]] = 1
        longest:int = 1

        while j<len(s):
            table[s[j]] = table.get(s[j], 0) +1
            most: str = max(table, key=table.get)

            # This gives the number of chars that can be replaced
            k_space = (j-i+1) - table[most] 
            if k_space > k:
                while (s[i] == most) and (table[most]>k+1):
                    table[s[i]] = table[s[i]] -1
                    i+=1
                    
                table[s[i]] = table[s[i]] -1
                i += 1 

            j+=1
            longest = max(longest, j-i)

            print(s[i:j], longest)

        return longest

if __name__ == "__main__":
    s = Solution()
    r = s.characterReplacement("aababba", 2)
    print(r)
