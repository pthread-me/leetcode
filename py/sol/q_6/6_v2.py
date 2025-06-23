#!/usr/bin/python3

class Solution:
    
        def convert(self, s: str, numRows: int) -> str:
            if numRows == 1:
                return s
            
            s_len = len(s)
            global_jump_size = (numRows)*2 - 2
            res = ""     

            for start_index in range(0, global_jump_size//2 +1):
                if start_index == 0 or start_index == global_jump_size//2:
                    local_jump_size = -1
                else:
                    local_jump_size = global_jump_size - start_index*2

                cur = start_index
                
                while cur < s_len:
                    res = res + s[cur]
                    print(f'cur: {cur}, jump: {global_jump_size}, {local_jump_size}')
                    
                    if local_jump_size != -1 and cur + local_jump_size < s_len:
                        res = res + s[cur + local_jump_size]
                        print(f'cur: {cur+local_jump_size}, jump: {global_jump_size}, {local_jump_size}')
                    cur = cur + global_jump_size


            return res            
            

if __name__ == "__main__":
    S = Solution()
    s: str = "paypalishiring"
    n: int = 3
    res = S.convert(s, n)
    print(res)
