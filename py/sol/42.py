#! /usr/bin/python3

# We keep a decreasing stack that tells us about the (top) aka the spots that water can occupy
# if e is < the top of the stack then its a decrease in height so we append it
# is e> top of the stack then it forms a right boundary that can trap water
#   we use the top of the stack to tell us of the depth of the water and stack[-2] tells us if
#   there is a left boundary. In the case where there is a left boundary we can calculated the bounded hight them * the dis
# otherwise if the area is not bounded, it means either the left boundary is deeper in the stack of ir does not exists
# so we simply pop the cur top and repeat, if the stack is empty then there is no left boundary so we break.

class Solution:
    def trap(self, height: list[int]) -> int:
        stack: list[int] = []
        res: int = 0

        for (i,e) in enumerate(height):
            print(stack, res)
            if len(stack) == 0:
                stack.append(i)
            elif height[stack[-1]] > e:
                stack.append(i)
            else:
                while len(stack)>0 and height[stack[-1]] < e:
                    top = stack.pop()
                    if len(stack)>0:
                        bounded_height = min(e, height[stack[-1]]) - height[top]
                        print(f"left:{stack[-1]}, middle:{top}, right:{i}, bounded: {bounded_height}, dis:{(i-stack[-1]-1)}")
                        res += bounded_height * (i-stack[-1] -1)
                    else:
                        break
                stack.append(i)
        return res 

if __name__ == "__main__":    
    S = Solution()
    r = S.trap([0,1,0,2,1,0,1,3,2,1,2,1])
    print(r)
