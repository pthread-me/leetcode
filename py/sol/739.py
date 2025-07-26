#! /usr/bin/python3

# We maintain a monotonic stack (on the indicies not temp) which saves the indices of values that we still
# havent found a larger temp for.

# for every e, we check if its larger than the elements in the stack, if so we have an answer
# for that element so we pop it, and repeat until we get to an element in the stack > e.

# we then push e into the stack as we also need to find a val > than it

class Solution:
    def dailyTemperatures(self, temperatures: list[int]) -> list[int]:
        stack: list[int] = []
        res: list[int] = [0] * len(temperatures)
        
        for (i, e) in enumerate(temperatures):
            if len(stack) < 1:
                stack.append(i)
                continue

            while len(stack) > 0 and temperatures[stack[-1]] < e:
                top = stack.pop()
                res[top] = i - top

            stack.append(i)

        return res




if __name__ == "__main__":    
    S = Solution()
    r = S.dailyTemperatures([73,74,75,71,69,72,76,73])
    print(r)

