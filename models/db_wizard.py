### we prepend t_ to tablenames and f_ to fieldnames for disambiguity


########################################
db.define_table('t_games',
    Field('f_grid', type='json',
          label=T('Grid')),
    Field('f_session', type='string',
          label=T('Session')),
    Field('f_player_mark', type='string', length=1,
          label=T('Player Mark')),
    Field('f_ai_mark', type='string', length=1,
          label=T('Ai Mark')),
    format='%(f_grid)s',
    migrate=settings.migrate,
    redefine=True)

db.define_table('t_games_archive',db.t_games,Field('current_record','reference t_games',readable=False,writable=False))
