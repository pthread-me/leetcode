#! /usr/bin/python3

# We maintain an initail hashtable of the freq in t.
# start by constructing the initial window (first itr of the loop)
#       By scanning j forward until all elem have a count <1.

# for future iter we first inc i by 1, then check j so that all elem in the table are <=0
# once j is set, we can move i forward until we break one of the conditions.

# The index before the cond is broken marks a min subarray, we get its length and comp to "sub"

# repeat until i>len or j is unable to satisfy the cond (meaning j reaches the end with some elem >0)
class Solution:
    def minWindow(self, s: str, t: str) -> str:
        if len(t)>len(s):
            return ""

        table:dict[str, int] = {}
        for e in t:
            table[e] = table.get(e,0) +1

        i= 0
        j= 0
        sub:tuple[float, int] = (float('inf'), 0)

        while i<len(s):
            while j<len(s):
                if all([table[e]<=0 for e in table]):
                    break
                elif s[j] in table:
                    table[s[j]] = table[s[j]] -1
                j += 1
            
            if any(table[e]>0 for e in table):
                break
            #else:
                #print(s[i:j+1])

            while i<len(s):
                if s[i] in table and table[s[i]]<0:
                    table[s[i]] = table[s[i]] +1
                    i+=1
                else:
                    break

            if i<len(s) and j<=len(s) and i<j:
                if sub[0]>j-i:
                    sub = (j-i,i)
            
            if i<len(s) and s[i] in table:
                table[s[i]] = table[s[i]] +1

            i+=1

        if sub[0] == float('inf'):
            return ""
        return s[sub[1]: sub[1]+int(sub[0])]

if __name__ == "__main__":
    s = Solution()
    r = s.minWindow("AAAA", "AA")
    print(r)
