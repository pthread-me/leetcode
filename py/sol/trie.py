class Trie:
    def __init__(self, c:str ):
        self.data: str = c
        self.is_end: bool = False
        self.children: dict[str, Trie] = {}

    def insert_chr(self, c:str):
        if c in self.children:
            return self.children[c]
        else:
            self.children[c] = Trie(c)
            return self.children[c]

    def insert(self, s: str):
        if len(s) == 0:
            return 

        child = self.insert_chr(s[0])
        if len(s[1:])== 0:
            child.is_end = True
        else:
            child.insert(s[1:])

    def p(self):
        print(f'{self.data}: {self.is_end}')
        for v in self.children.values():
            print(f'\t {v.data}')

        for v in self.children.values():
            v.p()
   
class Solution:
    def longestCommonPrefix(self, strs: list[str]) -> str:
        if "" in strs:
            return ""

        root = Trie("")
        for s in strs:
            root.insert(s)
        
        res = ""
        cur = root
        while len(cur.children.keys()) == 1 and cur.is_end == False:
            child_key, child_val = list(cur.children.items())[0] 
            res = res + child_val.data
            cur = cur.children[child_key]
        
        return res

if __name__ == "__main__":
    s = Solution()
    t = s.longestCommonPrefix(["a", "ab"])
    print(t)
