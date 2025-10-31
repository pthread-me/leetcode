#! /usr/bin/python3


def mergeSort(a:list[int]) -> list[int]:
    if len(a) < 1:
        return [-1]

    if len(a) == 1:
        return a

    l,r = mergeSort(a[:len(a)//2]), mergeSort(a[len(a)//2:])
    
    res:list[int] = []
    i,j = 0,0
    while i<len(l) and j<len(r):
        if l[i] < r[j]:
            res.append(l[i])
            i+=1
        else:
            res.append(r[j])
            j+=1

    if i<len(l):
        res = res + l[i:]
    elif j<len(r):
        res = res + r[j:]

    return res

    
        
if __name__ == "__main__":
    a:list[int] = [3,4,1,0,99,-12]
    print(mergeSort(a))
