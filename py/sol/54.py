#! /usr/bin/python3

# Im just tracing through the movement while maintaing row and column coundaries

class Solution:
    def spiralOrder(self, A: list[list[int]]) -> list[int]:
        res:list[int] = []
        
        r_start: int = 0
        r_end: int = len(A)

        c_start: int = 0
        c_end: int = len(A[0])

        q:int = 0   # row pointer
        p: int = 0  # column pointer

        while r_start < r_end and c_start < c_end:

            # left scan
            while p < c_end:
                print(A[q][p])
                res.append(A[q][p])
                p += 1
            
            p -= 1  # offset correction
            r_start += 1
            c_end -= 1
            q = r_start
            
            # down scan
            while q<r_end:
                res.append(A[q][p])
                q += 1

            q -= 1  # offset correction 
            p -= 1  # avoid double adding last element


            # righ scan
            while r_start < r_end and p >= c_start:
                res.append(A[q][p])
                p -= 1

            p = c_start  # offset correction
            q -= 1


            # up scan
            while c_start < c_end and q >= r_start:
                res.append(A[q][p])
                q -= 1

            c_start += 1
            q += 1  # offset correction
            p += 1  # avoid double adding
            r_end -= 1
       
        return res



if __name__ == "__main__":
    s = Solution()
    r = s.spiralOrder([[7],[9],[6]])
    print(r)
