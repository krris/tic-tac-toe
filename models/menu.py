response.title = settings.title
response.subtitle = settings.subtitle
response.author = settings.author
response.meta.author = '%(author)s <%(author_email)s>' % settings
response.meta.keywords = settings.keywords
response.meta.description = settings.description
response.menu = [
(T('Aktualna gra'),URL('default','index')==URL(),URL('default','index'),[]),
(T('Nowa gra'),URL('default','reset')==URL(),URL('default','reset'),[]),
]
