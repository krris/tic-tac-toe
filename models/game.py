# coding: utf8
#import pdb
from operator import add

def check_win(grid, movement, sign):
    directions = [[0, 1], [1, 1], [1, 0], [1, -1]]
    for d in directions :
        hit = 1
        for i in range(2):
            move = map(add, movement, d)
            while move[0]>=0 and move[1]>=0 and move[0]<len(grid) and move[1]<len(grid[0]) and grid[move[0]][move[1]] == sign:
                hit += 1
                move = map(add, move, d)
            if hit >= settings.marks_to_win:
                return True
            d[:] = [x*(-1) for x in d]
    return False


def check_draw(grid):
    empty = sum(1 for row in grid for i in row if i=='')                 
    if empty == 0:
        return True
    else:
        return False
