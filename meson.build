project('breakout', 'c', default_options : ['c_std=c11'])

sdl2 = dependency('sdl2')
sdl2_ttf = dependency('sdl2_ttf')

executable('breakout',
  'ball.c',
  'breakout.c',
  'brick.c',
  'collision.c',
  'main.c',
  'paddle.c',
  dependencies : [sdl2, sdl2_ttf]
)
