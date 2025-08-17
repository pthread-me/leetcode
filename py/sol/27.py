#! /usr/bin/python3

class Solution:
    table: dict[str, list[str]] = {
            "2" : ["a", "b", "c"],
            "3": ["d", "e", "f"],
            "4": ["g", "h", "i"],
            "5": ["j", "k", "l"],
            "6": ["m", "n", "o"],
            "7": ["p", "q", "r", "s"],
            "8": ["t", "u", "v"],
            "9": ["w", "x", "y", "z"]}     



    def combine(self, l1: list[str], l2: list[str]) -> list[str]:
        combination: list[str] = []
        for p in l1:
            for q in l2:
                combination.append(p+q)

        return combination

    def letterCombinations(self, digits: str) -> list[str]:
        if len(digits) < 1:
            return []

        if len(digits) == 4 and digits[0:2] == digits[2:4]:
            temp = self.combine(self.table[digits[0]], self.table[digits[1]])
            return self.combine(temp, temp)

        cur:list[str] = self.table[digits[0]]

        for e in digits[1:]:
            cur = self.combine(cur, self.table[e])

        return cur


if __name__ == "__main__":
    s = Solution()
    r = s.letterCombinations("2222")
    print(r)
