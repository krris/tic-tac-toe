# -*- coding: utf-8 -*-
import copy

max_depth = 9

class State:
    def __init__(self, grid=None, player_to_move=None, 
                last_move=None, utility=None):
        self.grid = grid
        self.player_to_move = player_to_move
        self.last_move = last_move
        self.utility = utility
    def copy(self):
        return copy.deepcopy(self)

def negamax(state, alpha, beta, depth=0):
    grid = state.grid
    player = state.player_to_move

    if terminalState(state) or depth > max_depth:
        evaluation = evaluate(grid, player)
        return State(grid, 
                    opponent(player), 
                    move if state.last_move == None else state.last_move, 
                    evaluation)

    maximum = State(utility = (- float('Inf')))
    #maximum = State(None, None, None, - float('Inf'))
    for move in moves(grid):
        grid_copy = copy.deepcopy(grid)
        make_move(grid_copy, move, player)
        new_state = State(grid_copy, 
                          opponent(player), 
                          move if state.last_move == None else state.last_move, 
                          0)

        new_alpha = alpha.copy()
        new_alpha.utility = (- alpha.utility)

        new_beta = beta.copy()
        new_beta.utility = (- beta.utility)

#        result = negamax(new_state, new_beta, new_alpha, depth=depth+1)
#        x = result
#        x.utility = - result.utility
        x = negamax(new_state, new_beta, new_alpha, depth=depth+1)
        x.utility = (- x.utility)
        if x.utility > maximum.utility:
            maximum = x

        if x.utility > alpha.utility:
            alpha = x
        if alpha.utility >= beta.utility:
            return alpha

    return maximum

def terminalState(state):
    grid = state.grid
    player = state.player_to_move
    if (winner(grid, player) or 
        winner(grid, opponent(player)) or 
        draw(grid)):
        return True
    return False

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

