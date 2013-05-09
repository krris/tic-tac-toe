# -*- coding: utf-8 -*-
import copy

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
    max_depth = settings.max_depth

    if terminalState(state) or depth > max_depth:
        evaluation = evaluate(grid, player)
        return State(grid, 
                    opponent(player), 
                    move if state.last_move == None else state.last_move, 
                    evaluation)

    maximum = State(utility = (- float('Inf')))
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
        GameStatus().draw(grid)):
        return True
    return False

def winner(grid, player):
    status = GameStatus()
    if (status.column_wins(grid, player) or
        status.row_wins(grid, player) or
        status.diagonal_wins(grid, player)):
        return True
    else:
        return False

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


class GameStatus:
    def __init__(self):
        self.width = settings.grid_size
        self.height = settings.grid_size
        self.marks_to_win = settings.marks_to_win

    def draw(self, grid):
        for x in range(settings.grid_size):
            for y in range(settings.grid_size):
                if grid[y][x] == '':
                    return False
        return True

    def column_wins(self, grid, player):
        for x in range(self.width):
            for y in range(self.height - self.marks_to_win + 1):
                counter = 0
                for i in range(self.marks_to_win):
                    if elem(grid, x, y+i) == player:
                        counter += 1
                    if counter == self.marks_to_win:
                        return True
        return False
    
    def row_wins(self, grid, player):
        for y in range(self.height):
            for x in range(self.width - self.marks_to_win + 1):
                counter = 0
                for i in range(self.marks_to_win):
                    if elem(grid,x+i,y) == player:
                        counter += 1
                    if counter == self.marks_to_win:
                        return True
        return False
    
    def diagonal_wins(self, grid, player):
        for x in range(self.width - self.marks_to_win + 1):
            for y in range(self.height - self.marks_to_win + 1):
                counter = 0
                for i in range(self.marks_to_win):
                    if elem(grid,x+i,y+i) == player:
                        counter += 1
                    if counter == self.marks_to_win:
                        return True
    
        for x in range(self.width - 1, self.width - self.marks_to_win, -1):
            for y in range(self.height - self.marks_to_win + 1):
                counter = 0
                for i in range(self.marks_to_win):
                    if elem(grid,x-i,y+i) == player:
                        counter += 1
                    if counter == self.marks_to_win:
                        return True
    
        return False
    
