# -*- coding: utf-8 -*-
import copy

def enum(**enums):
    return type('Enum', (), enums)

max_depth = 6
sign = enum(HUMAN=1, AI=-1)

def negamax(grid, depth, player):
    if (game_over(grid) or depth > max_depth):
        if player == settings.player_mark:
            return sign.HUMAN * evaluate(grid)
        elif player == settings.ai_mark:
            return sign.AI * evaluate(grid)

    max = - float('Inf')
    for move in moves(grid):
        grid_copy = copy.deepcopy(grid)
        make_move(grid_copy, move, player)
        x = - negamax(grid_copy, depth+1, opponent(player))
        if x > max:
            max = x
    return max


def game_over(grid):
    pass

def evaluate(grid):
    pass

def moves(grid):
    pass

def make_move(grid, move, player):
    pass
