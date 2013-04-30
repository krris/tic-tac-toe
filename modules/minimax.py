from utils import *
# State contains:
# grid, moves, player_to_move, utility 

def ai_minimax_move(state):
    move = minimax_decision(state)
    return result(state, move)


def minimax_decision(state):
    player = state.player_to_move

    def max_value(state):
        if terminal_test(state):
            return utility(state, player)
        v = -infinity
        for a in actions(state):
            v = max(v, min_value(result(state, a)))
        return v

    def min_value(state):
        if terminal_test(state):
            return utility(state, player)
        v = infinity
        for a in actions(state):
            v = min(v, max_value(result(state, a)))
        return v

    # Body of minimax_decision:
    return argmax(actions(state),
                  lambda a: min_value(result(state, a)))


def terminal_test(state):
    "A state is terminal if it is won or there are no empty squares."
    return state.utility != 0 or len(state.moves) == 0

def utility(state, player):
    "Return the value to player: 1 for win, -1 for loss, 0 otherwise."
    if player == settings.ai_mark:
        return state.utility
    else:
        return -state.utility

def actions(state):
    "Return a list of the allowable moves at current state."
    return state.moves

def result(state, move):
    "Return the state that results from making a move from a state."
    if move not in state.moves:
        return state # Illegal move has no effect
    grid = state.grid
    (x, y) = move
    grid[x][y] = state.player_to_move

    moves = list(state.moves)
    moves.remove(move)
    return Struct(player_to_move=if_(state.player_to_move == settings.ai_mark,
                                     settings.player_mark, settings.ai_mark),
                  utility=compute_utility(grid, move, state.player_to_move),
                  grid=grid,
                  moves=moves)

def compute_utility(grid, move, player):
    "If X wins with this move, return 1; if O return -1; else return 0."
    if (self.k_in_row(grid, move, player, (0, 1)) or
        self.k_in_row(grid, move, player, (1, 0)) or
        self.k_in_row(grid, move, player, (1, -1)) or
        self.k_in_row(grid, move, player, (1, 1))):
        return if_(player == settings.ai_mark, +1, -1)
    else:
        return 0

def k_in_row(grid, move, player, (delta_x, delta_y)):
    "Return true if there is a line through move on grid for player."
    x, y = move
    n = 0 # n is number of moves in row
    while grid[x][y] == player:
        n += 1
        x, y = x + delta_x, y + delta_y
    x, y = move
    while grid[x][y] == player:
        n += 1
        x, y = x - delta_x, y - delta_y
    n -= 1 # Because we counted move itself twice
    return n >= self.k   

    
    
class Struct:
    """Create an instance with argument=value slots.
    This is for making a lightweight object whose class doesn't matter."""
    def __init__(self, **entries):
        self.__dict__.update(entries)

    def __cmp__(self, other):
        if isinstance(other, Struct):
            return cmp(self.__dict__, other.__dict__)
        else:
            return cmp(self.__dict__, other)

    def __repr__(self):
        args = ['%s=%s' % (k, repr(v)) for (k, v) in vars(self).items()]
        return 'Struct(%s)' % ', '.join(sorted(args))
