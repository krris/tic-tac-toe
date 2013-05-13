import game_status

def convert(grid):
    matrix = game_status.StringMatrix()
    for y in range(settings.grid_size):
        row = game_status.StringVec()
        for x in range(settings.grid_size):
            row.append(grid[y][x])
        matrix.append(row)
    return matrix
