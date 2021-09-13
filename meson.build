project('breakout', 'c')

sdl2 = dependency('sdl2')
sdl2_ttf = dependency('sdl2_ttf')

executable('breakout',
  'ball.c',
  'breakout.c',
  'brick.c',
  'main.c',
  'paddle.c',
  dependencies : [sdl2, sdl2_ttf]
)
