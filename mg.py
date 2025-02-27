import pygame
import sys
import heapq

# Define grid size and colors
WINDOW_SIZE = (1000, 1000)  # Increased window size
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
YELLOW = (255, 255, 0)

pygame.init()
screen = pygame.display.set_mode(WINDOW_SIZE)
clock = pygame.time.Clock()

def draw_grid(grid, path=None):
    cell_width = WINDOW_SIZE[0] // len(grid[0])
    cell_height = WINDOW_SIZE[1] // len(grid)
    for i in range(len(grid)):
        for j in range(len(grid[0])):
            color = WHITE
            if grid[i][j] == 1:
                color = BLACK
            elif grid[i][j] == -1:
                color = RED
            pygame.draw.rect(screen, color, (j * cell_width, i * cell_height, cell_width, cell_height))
            pygame.draw.rect(screen, BLACK, (j * cell_width, i * cell_height, cell_width, cell_height), 1)
    
    if path:
        for i, j in path:
            pygame.draw.rect(screen, GREEN, (j * cell_width, i * cell_height, cell_width, cell_height))

def dijkstra(grid, start, end):
    rows, cols = len(grid), len(grid[0])
    dist = [[float('inf')] * cols for _ in range(rows)]
    dist[start[0]][start[1]] = 0
    pq = [(0, start)]
    parent = {start: None}
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    
    while pq:
        d, (x, y) = heapq.heappop(pq)
        if (x, y) == end:
            break
        for dx, dy in directions:
            nx, ny = x + dx, y + dy
            if 0 <= nx < rows and 0 <= ny < cols and grid[nx][ny] != 1:
                new_dist = d + (10 if grid[nx][ny] == 0 else 50)
                if new_dist < dist[nx][ny]:
                    dist[nx][ny] = new_dist
                    heapq.heappush(pq, (new_dist, (nx, ny)))
                    parent[(nx, ny)] = (x, y)
    
    path = []
    node = end
    while node:
        path.append(node)
        node = parent.get(node)
    path.reverse()
    return path

# Take input for grid size
rows = int(input("Enter number of rows: "))
cols = int(input("Enter number of columns: "))
grid = [[0] * cols for _ in range(rows)]

# Take input for obstacles
num_obstacles = int(input("Enter number of obstacles: "))
obstacles = []
for _ in range(num_obstacles):
    r, c = map(int, input("Enter obstacle position (row col): ").split())
    obstacles.append((r, c))

# Take input for danger zones
num_dangers = int(input("Enter number of danger zones: "))
dangers = []
for _ in range(num_dangers):
    r, c = map(int, input("Enter danger position (row col): ").split())
    dangers.append((r, c))

# Take input for start and end points
start = tuple(map(int, input("Enter start position (row col): ").split()))
end = tuple(map(int, input("Enter end position (row col): ").split()))

for r, c in obstacles:
    grid[r][c] = 1
for r, c in dangers:
    grid[r][c] = -1

running = True
visualize_dijkstra = False
path = []
while running:
    screen.fill(WHITE)
    draw_grid(grid, path if visualize_dijkstra else None)
    pygame.display.flip()
    
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_d:
                visualize_dijkstra = True
                path = dijkstra(grid, start, end)
    
    clock.tick(30)
pygame.quit()
