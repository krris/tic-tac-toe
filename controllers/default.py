# -*- coding: utf-8 -*-
import json
import random
#import game
from minimax import ai_minimax_move

### required - do no delete
def user(): return dict(form=auth())
def download(): return response.download(request,db)
def call(): return service()
### end requires

def index():   
    if(session.game_grid == None):
        # Information about state of the game
        # Create grid and save
        grid = [['' for row in range(settings.grid_size)] for col in range(settings.grid_size)]
        session.game_grid = grid
        session.game_finished = False
        
        # Possible moves in a current state (list of (x, y))
        moves = []
        for row in range(settings.grid_size):
            for column in range(settings.grid_size):
                moves.append((row, column))
        session.moves = moves

    else:
        # Load grid
        grid = session.game_grid
        moves = session.moves
        

    
    # Variables passed to view
    view_data = dict(
        grid_size = settings.grid_size, 
        grid = grid, 
        moves = moves,
        player_mark = settings.player_mark, 
        ai_mark = settings.ai_mark,
        game_finished = session.game_finished,
        url_move = URL('move'),
        url_reset = URL('reset')
    )
    
    return view_data
    

def move():
    
    if(request.post_vars.i == None or request.post_vars.j == None or session.game_finished):
        return False
        
    i = int(request.post_vars.i)
    j = int(request.post_vars.j)
    grid = session.game_grid
    moves = session.moves
    
    if(i >= settings.grid_size or j >= settings.grid_size or i < 0 or j < 0 or grid[i][j] != ''):
        return False
    
    grid[i][j] = settings.player_mark
    moves.remove((i, j))
    
    if check_win(grid, [i, j], settings.player_mark):
        session.game_grid = grid
        session.game_finished = True
        return json.dumps({'status':'player_won'});

    [x, y] = ai_move(grid, moves)
    grid[x][y] = settings.ai_mark
    #moves.remove((x, y))
    
    if check_win(grid, [x, y], settings.ai_mark):
        status = 'ai_won'
        session.game_finished = True
    elif check_draw(grid):
        status = 'draw'
        session.game_finished = True
    else:
        status = 'none'
        
    session.game_grid = grid
    session.moves = moves
    return json.dumps({'x':x, 'y':y, 'status':status})     
   

def ai_move(grid, moves):
    x = random.randint(0,settings.grid_size-1)
    y = random.randint(0,settings.grid_size-1)
    while(grid[x][y]!=''):
        x = random.randint(0,settings.grid_size-1)
        y = random.randint(0,settings.grid_size-1)
    return [x, y]
    
def reset():
    session.game_grid = None
    session.game_finished = False
    redirect(URL('index'))
    return False
