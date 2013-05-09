# coding: utf8
#import pdb
from operator import add

def check_win(grid, move, player):
    if (k_in_row(grid, move, player, (0, 1)) or
        k_in_row(grid, move, player, (1, 0)) or
        k_in_row(grid, move, player, (1, -1)) or
        k_in_row(grid, move, player, (1, 1))):
        return True
    else:
        return False

def k_in_row(grid, move, player, (delta_x, delta_y)):
    "Return true if there is a line through move on grid for player."
    x, y = move
    n = 0 # n is number of moves in row
    while safe_list_get(grid, x) != None and safe_list_get(grid[x], y) == player:
        n += 1
        x, y = x + delta_x, y + delta_y
    x, y = move
    while safe_list_get(grid, x) != None and safe_list_get(grid[x], y) == player:
        n += 1
        x, y = x - delta_x, y - delta_y
    n -= 1 # Because we counted move itself twice
    return n >= settings.marks_to_win   

def safe_list_get (l, idx, default=None):
    if idx < 0:
        return default
    try:
        return l[idx]
    except IndexError:
        return default


def check_draw(grid):
    empty = sum(1 for row in grid for i in row if i=='')                 
    if empty == 0:
        return True
    else:
        return False
