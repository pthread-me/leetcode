#! /usr/bin/python3

import heapq


# We want to perform a bfs starting from the limiting factor, so we look at boundaries and start with the min (using a heap)
# the amount of water any neighboring cell can hold is at most its min boundary (which we have) so all we need to do
# is pop, check if neighboor is visited, if not add as much water as possible (aka min boundary - cell height) then the 
# cell becomes a boundary. repeat until all cells are processed
class Solution:
    def trapRainWater(self, heightMap: list[list[int]]) -> int:
        water: int = 0
        boundary: list[tuple[int, int, int]] =  []
        visited: list[list[bool]] = [[False for _ in row] for row in heightMap]

        for j in range(0, len(heightMap[0])):
            boundary.append((heightMap[0][j], 0, j))
            boundary.append((heightMap[len(heightMap)-1][j], len(heightMap)-1, j))

            visited[0][j] = True
            visited[len(heightMap)-1][j] = True

        for i in range(1, len(heightMap)-1):
            boundary.append((heightMap[i][0], i, 0))
            boundary.append((heightMap[i][len(heightMap[i])-1], i, len(heightMap[i])-1))

            visited[i][0] = True
            visited[i][len(heightMap[i])-1] = True

        heapq.heapify(boundary)


        def fill(b_height:int, i:int,  j:int):
            filled_by = 0
            if heightMap[i][j]<b_height:
                filled_by = b_height - heightMap[i][j]
                heightMap[i][j] = b_height 

            if filled_by > 0:
                print(f"Filled: {i, j} by { filled_by} to {heightMap[i][j]}")

            heapq.heappush(boundary, (heightMap[i][j], i, j))
            return filled_by 

        while len(boundary) > 0:
            e = heapq.heappop(boundary)
            (b_height, i, j) = e
            
            dir = [-1, 1]

            for d in dir:
                if 0 <= i + d < len(heightMap) and visited[i+d][j] == False:
                    water += fill(b_height, i+d, j)
                    visited[i+d][j] = True
            for d in dir:
                if 0 <= j + d < len(heightMap[0]) and visited[i][j+d] == False:
                    water += fill(b_height, i, j+d)
                    visited[i][j+d] = True

        return water

if __name__ == "__main__":
    s = Solution()
    r = s.trapRainWater([[12,13,1,12],[13,4,13,12],[13,8,10,12],[12,13,12,12],[13,13,13,13]])
    print(r)
