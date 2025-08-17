#! /usr/bin/python3



# We first need to mirror on the horizontal axis, then transpose on the diagonal 
# make sure when transposing we dont swap the pair i,j twice
class Solution:
    def rotate(self, A: list[list[int]]) -> None:
        n = len(A)-1
        
        for i in range(0, len(A)//2):
            for j in range(0, len(A)):
                temp = A[i][j]
                A[i][j] = A[n-i][j]
                A[n-i][j] = temp
       
        print()
        for e in A:
            print(e)       
        
        for i in range(0, len(A)):
            for j in range(i, len(A)):
                temp = A[i][j]
                A[i][j] = A[j][i]
                A[j][i] = temp


if __name__ == "__main__":
    s = Solution()
    A = [[1,2,3],[4,5,6],[7,8,9]]
    for e in A:
        print(e)
    r = s.rotate(A)
    print()
    for e in A:
        print(e)
