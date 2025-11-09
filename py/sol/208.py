#! /usr/bin/python3
from typing import Self

class Trie:    
    def __init__(self):
        self.val: str = ""
        self.children:list[Trie] = []
    
    def insert(self, word: str) -> None:
        self.__insert__(word+"$")

    def __insert__(self, word: str) -> None:
        if len(word) == 0:
            return

        child: Trie|None = None
        for c in self.children:
            if c.val == word[0]:
                child = c
                break
        
        if child is None:
            child = Trie()
            child.val = word[0]
            self.children.append(child)
            child.__insert__(word[1:])
        else:
            child.__insert__(word[1:])

    
    def search(self, word:str) -> bool:
        return self.__search__(word+"$")

    def startsWith(self, prefix: str) -> bool:
        return self.__search__(prefix)

    def __search__(self, word: str) -> bool:
        if len(word) == 0:
            return True

        for c in self.children:
            if c.val == word[0]:
                return c.__search__(word[1:])
        
        return False


if __name__ == "__main__":
    t: Trie = Trie()
    t.insert("apple")
    print(t.search("apple"))
