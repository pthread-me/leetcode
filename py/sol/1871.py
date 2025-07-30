#! /usr/bin/python3


# I still am not great at dp:
# The state that we save here is the value of the window.
# we set indices that are reachible to 1, first init the window by setting dp[0] to 1
# and walking until we reach maxJump. window is then the sum of dp[0, maxJump-minJump+1] (inclusive)

# Then for every index after maxJump, we shift the window, so sub the first index of the window and add the index right after
# finaly dp[-1] tells us whether the last index is reachible or not.
class Solution:
    def canReach(self, s: str, minJump: int, maxJump: int) -> bool:
        dp = [1 if i == 0 else 0 for (i,_) in enumerate(s)]
        

        for i in range(1, maxJump+1):
            if i >= len(s):
                break
            
            if i >= minJump and s[i] == "0":
                dp[i] = 1
            else:
                dp[i] = 0

        if maxJump + 1 >= len(s):
            return dp[-1] == 1
        
        window: int = sum(dp[0:maxJump-minJump+1])
        
        for i in range(maxJump + 1, len(s)):
            window = window - (dp[i-maxJump-1]) + dp[i-minJump]

            if window > 0 and s[i] == "0":
                dp[i] = 1
            else:
                dp[i] = 0

            print(dp, window)
        return dp[-1] == 1


if __name__ == "__main__":    
    S = Solution()
    with open("input.txt", "r") as f:
        input = f.read().strip()

    input: str = open("input.txt").read().strip()
    r = S.canReach("01101110", 2, 3)
    print(r)
