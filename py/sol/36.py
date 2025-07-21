#! /usr/bin/python3

# My solution is kinda dumb and uses hashsets + hashmaps
# We can do this more elegantly by having a list of pairs
# res = (i, e) (j, e) (block, e) for all e
# if 2 eelements share the same row/col/block then at least
# one of their pairs match so by getting the set then comparing against the original size we can determine if any were equal

class MySolution:
    def isValidSudoku(self, A: list[list[str]]) -> bool:
        block_map: dict[int, set[str]] = {}
        j_map: dict[int, set[str]] = {}
        for i in range(0, len(A)):
            i_set: set[str] = set()
            for j in range(0, len(A[i])):
                
                if not (i//3)*10 + (j//3) in block_map.keys():
                    block_map[(i//3)*10 + (j//3)] = set()
                if not j in j_map.keys():
                    j_map[j] = set()
                
                if not A[i][j] == ".":
                    if (A[i][j] in i_set) or (A[i][j] in j_map[j]) or (A[i][j] in block_map[(i//3)*10 + (j//3)]):
                        return False
                    else:
                        i_set.add(A[i][j])
                        j_map[j].add(A[i][j])
                        block_map[(i//3)*10 + (j//3)].add(A[i][j])
                

        return True

class Solution:
    def isValidSudoku(self, A: list[list[str]]) -> bool:
        res: list[tuple[str, int, str]] = []

        for i in range(0, len(A)):
            for j in range(0, len(A[i])):
                if not A[i][j] == ".": 
                    res += [("i",i, A[i][j]), ("j", j, A[i][j]), ("b", (i//3)*10 + (j//3), A[i][j])]

        return len(res) == len(set(res))



if __name__ == "__main__":
    s= Solution()
    r = s.isValidSudoku([["5","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]])
    
    print(r)
