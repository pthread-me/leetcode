#!/usr/bin/python3

def counting_sort(l: list[int]):
    maximum = max(l)
    count = [0] * (maximum+1)
    res = [0] * len(l)

    for e in l:
        count[e] += 1
   
   #cumulative sum
    for i in range(1, len(count)):
        count[i] += count[i-1]

    for e in l[::-1]:
        res[count[e] -1] = e
        count[e] -=1
    return res


def extract(num:int, modulo:int , divisor:int) -> int:
    return (num % modulo) // divisor

# i is the power of 10
def counting_sort_i(l:list[int], i: int) -> list[int]:
    count = [0] * (10)
    res = [0] * len(l)
    modulo = 10 ** i
    divsor = 10 ** (i-1)

    for e in l:
        count[extract(e, modulo, divsor)] += 1

    # cummulate
    for i in range(1, len(count)):
        count[i] += count[i-1]

    for e in l[::-1]:
        res[count[extract(e, modulo, divsor)] -1] = e
        count[extract(e, modulo, divsor)] -=1

    return res


def radix_sort(l: list[int]) -> list[int]:
    res = l
    m = max(l)
    digits = 0

    while m//(10** digits) > 0:
        digits += 1
    
    for i in range(1, digits +1):
        res = counting_sort_i(res, i)

    return res

if __name__ == "__main__":
#    s= Solution()
#    r = s.isAnagram("anagram", "nagaram")
    r = radix_sort([107, 45, 75, 90, 802, 24, 2, 66])
    print(r)
