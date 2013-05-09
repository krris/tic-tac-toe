# -*- coding: utf-8 -*-
import copy

def enum(**enums):
    return type('Enum', (), enums)

max_depth = 3
sign = enum(HUMAN=1, AI=-1)

class State:
    def __init__(self, grid, player_to_move, last_move, utility):
        self.grid = grid
        self.player_to_move = player_to_move
        self.last_move = last_move
        self.utility = utility

def negamax(state, depth=0):
    grid = state.grid
    player = state.player_to_move

    if (winner(grid, player) or winner(grid, opponent(player)) or draw(grid) or depth > max_depth):
        evaluation = evaluate(grid, player)
        return State(grid, opponent(player), move if state.last_move == None else state.last_move, evaluation)

    maximum = State(None, None, None, - float('Inf'))
    for move in moves(grid):
        grid_copy = copy.deepcopy(grid)
        make_move(grid_copy, move, player)
        new_state = State(grid_copy, opponent(player), move if state.last_move == None else state.last_move, 0)
        result = negamax(new_state, depth=depth+1)
        x = result
        x.utility = - result.utility

        if x.utility > maximum.utility:
            maximum = x

    return maximum


def winner(grid, player):
    if (column_wins(grid, settings.grid_size, settings.grid_size, settings.marks_to_win, player) or
        row_wins(grid, settings.grid_size, settings.grid_size, settings.marks_to_win, player) or
        diagonal_wins(grid, settings.grid_size, settings.grid_size, settings.marks_to_win, player)):
        return True
    else:
        return False

def draw(grid):
    for x in range(settings.grid_size):
        for y in range(settings.grid_size):
            if grid[y][x] == '':
                return False
    return True

def evaluate(grid, player):
    isXWon = winner(grid, settings.player_mark)
    isOWon = winner(grid, settings.ai_mark)

    if isXWon:
        return 1 if player == settings.player_mark else -1
    elif isOWon:
        return 1 if player == settings.ai_mark else -1
    else:
        return 0

def moves(grid):
    moves = []
    for x in range(settings.grid_size):
        for y in range(settings.grid_size):
            if grid[y][x] == '':
                moves.append( (y, x) )
    return moves

def make_move(grid, move, player):
    (y, x) = move
    grid[y][x] = player

def opponent(player):
    if player == settings.player_mark:
        return settings.ai_mark
    else:
        return settings.player_mark

def elem(grid, x, y, default=None):
    if x < 0 or y < 0:
        return default
    else:
        return grid[y][x]


def column_wins(grid, width, height, marks_to_win, player):
    for x in range(width):
        for y in range(height - marks_to_win + 1):
            counter = 0
            for i in range(marks_to_win):
                if elem(grid, x, y+i) == player:
                    counter += 1
                if counter == marks_to_win:
                    return True
    return False

def row_wins(grid, width, height, marks_to_win, player):
    for y in range(height):
        for x in range(width - marks_to_win + 1):
            counter = 0
            for i in range(marks_to_win):
                if elem(grid,x+i,y) == player:
                    counter += 1
                if counter == marks_to_win:
                    return True
    return False

def diagonal_wins(grid, width, height, marks_to_win, player):
    for x in range(width - marks_to_win + 1):
        for y in range(height - marks_to_win + 1):
            counter = 0
            for i in range(marks_to_win):
                if elem(grid,x+i,y+i) == player:
                    counter += 1
                if counter == marks_to_win:
                    return True

    for x in range(width - 1, width - marks_to_win, -1):
        for y in range(height - marks_to_win + 1):
            counter = 0
            for i in range(marks_to_win):
                if elem(grid,x-i,y+i) == player:
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
                if (elem(grid,x,y+i) == player or
                   elem(grid,x,y+i) == ''):
                    n += 1
                if n == marks_to_win:
                    counter += 1
    return counter

def count_row(grid, width, height, marks_to_win, player):
    for y in range(height):
        for x in range(width - marks_to_win + 1):
            counter = 0
            for i in range(marks_to_win):
                if elem(grid,x+i,y) == player:
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



#def winning_columns(width, height, marks_to_win):
#    columns = []
#    for x in range(width):
#        for y in range(height - marks_to_win + 1):
#            col = [] 
#            for i in range(marks_to_win):
#                col.append( (x, y + i) )
#            columns.append(col)
#    return columns
#
#def winning_rows(width, height, marks_to_win):
#    rows = []
#    for y in range(height):
#        for x in range(width - marks_to_win + 1):
#            row = [] 
#            for i in range(marks_to_win):
#                row.append( (x + i, y) )
#            rows.append(row)
#    return rows
#
#def winning_diagonals(width, height, marks_to_win):
#    diagonals = []
#    for x in range(width - marks_to_win + 1):
#        for y in range(height - marks_to_win + 1):
#            diag = [] 
#            for i in range(marks_to_win):
#                diag.append( (x + i, y + i) )
#            diagonals.append(diag)
#
#    for x in range(width - 1, width - marks_to_win, -1):
#        for y in range(height - marks_to_win + 1):
#            diag = [] 
#            for i in range(marks_to_win):
#                diag.append( (x - i, y + i) )
#            diagonals.append(diag)
#
#    return diagonals
#
#    
#
#
#
#
#
#
#
#
#
#

