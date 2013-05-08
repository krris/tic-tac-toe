# -*- coding: utf-8 -*-
import copy

def enum(**enums):
    return type('Enum', (), enums)

max_depth = 3
sign = enum(HUMAN=1, AI=-1)

def negamax(grid, depth, player):
    if (game_over(grid, player) or depth > max_depth):
        if player == settings.player_mark:
            return sign.HUMAN * evaluate(grid)
        elif player == settings.ai_mark:
            return sign.AI * evaluate(grid)

    maximum = - float('Inf')
    for move in moves(grid):
        grid_copy = copy.deepcopy(grid)
        make_move(grid_copy, move, player)
        x = - negamax(grid_copy, depth+1, opponent(player))
        if x > maximum:
            maximum = x
    return maximum


def game_over(grid, player):
    if (column_wins(grid, settings.grid_size, settings.grid_size, settings.marks_to_win, player) or
        row_wins(grid, settings.grid_size, settings.grid_size, settings.marks_to_win, player) or
        diagonal_wins(grid, settings.grid_size, settings.grid_size, settings.marks_to_win, player)):
        return True
    else:
        return False

def evaluate(grid):
    if game_over(grid, settings.player_mark):
        return +5
    elif game_over(grid, settings.ai_mark):
        return -5
    else:
        return 0

def moves(grid):
    moves = []
    for x in range(settings.grid_size):
        for y in range(settings.grid_size):
            if grid[x][y] == '':
                moves.append( (x, y) )
    return moves

def make_move(grid, move, player):
    (x, y) = move
    grid[x][y] = player

def opponent(player):
    if player == settings.player_mark:
        return settings.ai_mark
    else:
        return settings.player_mark

def column_wins(grid, width, height, marks_to_win, player):
    for x in range(width):
        for y in range(height - marks_to_win + 1):
            counter = 0
            for i in range(marks_to_win):
                if grid[y+i][x] == player:
                    counter += 1
                if counter == marks_to_win:
                    return True
    return False

def row_wins(grid, width, height, marks_to_win, player):
    for y in range(height):
        for x in range(width - marks_to_win + 1):
            counter = 0
            for i in range(marks_to_win):
                if grid[y][x+i] == player:
                    counter += 1
                if counter == marks_to_win:
                    return True
    return False

def diagonal_wins(grid, width, height, marks_to_win, player):
    for x in range(width - marks_to_win + 1):
        for y in range(height - marks_to_win + 1):
            counter = 0
            for i in range(marks_to_win):
                if grid[y+i][x+i] == player:
                    counter += 1
                if counter == marks_to_win:
                    return True

    for x in range(width - 1, width - marks_to_win, -1):
        for y in range(height - marks_to_win + 1):
            counter = 0
            for i in range(marks_to_win):
                if grid[y+i][x-i] == player:
                    counter += 1
                if counter == marks_to_win:
                    return True

    return False

def count_column(grid, width, height, marks_to_win, player):
    counter = 0
    for x in range(width):
        for y in range(height - marks_to_win + 1):
            n = 0
            for i in range(marks_to_win):
                if (grid[y+i][x] == player or
                   grid[y+i][x] == ''):
                    n += 1
                if n == marks_to_win:
                    counter += 1
    return counter

def count_row(grid, width, height, marks_to_win, player):
    for y in range(height):
        for x in range(width - marks_to_win + 1):
            counter = 0
            for i in range(marks_to_win):
                if grid[y][x+i] == player:
                    counter += 1
                if counter == marks_to_win:
                    return True
    return False

#def count_diagonal(width, height, marks_to_win, player):
#    for x in range(width - marks_to_win + 1):
#        for y in range(height - marks_to_win + 1):
#            counter = 0
#            for i in range(marks_to_win):
#                if grid[y+i][x+i] == player:
#                    counter += 1
#                if counter == marks_to_win:
#                    return True
#
#    for x in range(width - 1, width - marks_to_win, -1):
#        for y in range(height - marks_to_win + 1):
#            counter = 0
#            for i in range(marks_to_win):
#                if grid[y+i][x-i] == player:
#                    counter += 1
#                if counter == marks_to_win:
#                    return True
#
#    return False



def winning_columns(width, height, marks_to_win):
    columns = []
    for x in range(width):
        for y in range(height - marks_to_win + 1):
            col = [] 
            for i in range(marks_to_win):
                col.append( (x, y + i) )
            columns.append(col)
    return columns

def winning_rows(width, height, marks_to_win):
    rows = []
    for y in range(height):
        for x in range(width - marks_to_win + 1):
            row = [] 
            for i in range(marks_to_win):
                row.append( (x + i, y) )
            rows.append(row)
    return rows

def winning_diagonals(width, height, marks_to_win):
    diagonals = []
    for x in range(width - marks_to_win + 1):
        for y in range(height - marks_to_win + 1):
            diag = [] 
            for i in range(marks_to_win):
                diag.append( (x + i, y + i) )
            diagonals.append(diag)

    for x in range(width - 1, width - marks_to_win, -1):
        for y in range(height - marks_to_win + 1):
            diag = [] 
            for i in range(marks_to_win):
                diag.append( (x - i, y + i) )
            diagonals.append(diag)

    return diagonals

    


temp = winning_rows(3,3,3)
temp = winning_rows(4,4,3)
temp = winning_diagonals(3,3,3)
temp = winning_diagonals(4,4,3)











