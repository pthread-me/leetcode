#! /usr/bin/python3

# literally forwrd-backward but on numbers
class Solution:
    def totalFruit(self, fruits: list[int]) -> int:
        prefix: list[int] = [0] * (len(fruits))
        s: set[int] = set()
        
        def backward(i: int)-> int:
            new_start: int = 0
            while i>-1:
                if len(s) <2 or fruits[i] in s:
                    new_start += 1
                    s.add(fruits[i])
                else:
                    break
                i -= 1
            return new_start

        prefix[0] = 1
        s.add(fruits[0])
        for i in range(1, len(fruits)):
            if len(s)<2 or fruits[i] in s:
                prefix[i] = prefix[i-1] + 1
                s.add(fruits[i])
            else:
                s.clear()
                s.add(fruits[i])
                prefix[i] = backward(i-1) + 1

        
        return  max(prefix)


if __name__ == "__main__":
    s = Solution()
    r = s.totalFruit([1,2,2,2,2,3,3,4,3,4,4,5])
    print(r)
