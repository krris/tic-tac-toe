# -*- coding: utf-8 -*-
import json
import random
import copy
import game 

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
        
    else:
        # Load grid
        grid = session.game_grid
    
    # Variables passed to view
    view_data = dict(
        grid_size = settings.grid_size, 
        grid = grid, 
        player_mark = settings.player_mark, 
        ai_mark = settings.ai_mark,
        game_finished = session.game_finished,
        url_move = URL('move'),
        url_reset = URL('reset')
    )
    
    return view_data

def move():

    game_settings = game.Settings.get_instance()
    game_settings.initialize(settings.grid_size, settings.grid_size, settings.marks_to_win,
                            settings.player_mark, settings.ai_mark)

    game_stat = game.Status(game_settings)
    
    if(request.post_vars.i == None or request.post_vars.j == None or session.game_finished):
        return False
        
    i = int(request.post_vars.i)
    j = int(request.post_vars.j)
    grid = session.game_grid
    
    if(i >= settings.grid_size or j >= settings.grid_size or i < 0 or j < 0 or grid[i][j] != ''):
        return False
    
    grid[i][j] = settings.player_mark
    last_player_move = (i,j)
    session.game_finished = True

    player_move = game.IntPair()
    player_move.first = i
    player_move.second = j
    
    [x, y] = [-1, -1] # Default values in case AI will not make move
    
    if game_stat.winner(convert(grid), player_move, settings.player_mark):        
        status = 'player_won'
    elif game_stat.draw(convert(grid)):
        status = 'draw'
    else:
        # Make AI move
        state = game.State(convert(copy.deepcopy(grid)), settings.ai_mark, 0)
        ai = game.Ai(game_settings, settings.max_depth)
        new_state = ai.move(state)

        new_move = new_state.get_last_move()
        x = new_move.first
        y = new_move.second
        grid[x][y] = settings.ai_mark
        
        ai_move = game.IntPair()
        ai_move.first = x
        ai_move.second = y
        if game_stat.winner(convert(grid), ai_move, settings.ai_mark):
            status = 'ai_won'
        elif game_stat.draw(convert(grid)):
            status = 'draw'
        else:
            status = 'none'
            session.game_finished = False # We keep on playing
        
    session.game_grid = grid
    return json.dumps({'x':x, 'y':y, 'status':status})     
    
def reset():
    session.game_grid = None
    session.game_finished = False
    redirect(URL('index'))
    return False
