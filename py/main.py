#! /usr/bin/python3

# We maintain a monotonically decreasing queue, s.t that first elem is the max
# for every new window, we check if the index that was just passed is the top of the queue
# if so we remove it since it can no longer be the max. We then check the newley added elem
# We remove every element from the queue that is smaller than the new elem (since its monotonic
# this only requires a left to right scan). Finally we check the top of the queue (q[0]) for the max

# This takes O(n) time since each elem is added to the queue once and removed at most once
# the queue size is at most k.

class Solution:
    def maxSlidingWindow(self, nums: list[int], k: int) -> list[int]:
        queue: list[int] = []
        top: list[int] = []
        
        for i in range(0, len(nums)):
            if len(queue) == 0:
                queue.append(nums[i])
            else:
                #remove old window starting elem
                if i-k>=0 and nums[i-k] == queue[0]:
                    queue = queue[1:]
                
                while len(queue)>0 and nums[i] > queue[-1]:
                    _ = queue.pop()
                queue.append(nums[i])
            
            if (i+1)-k>=0:
                top.append(queue[0])
        
        return top

if __name__ == "__main__":
    s = Solution()
    r = s.maxSlidingWindow([1,3,-1,-3,5,3,6,7], 3)
    print(r)
