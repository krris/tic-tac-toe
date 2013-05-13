import game

def convert(grid):
    matrix = game.StringMatrix()
    for y in range(settings.grid_size):
        row = game.StringVec()
        for x in range(settings.grid_size):
            row.append(grid[y][x])
        matrix.append(row)
    return matrix
