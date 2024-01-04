build:
	gcc ./src/main.c ./src/figure.c ./src/element.c ./src/figure_list.c $$(pkg-config --cflags --libs sdl2 SDL2_ttf) -o ./bin/tetris && ./bin/tetris
test:
	gcc ./tests/main.c ./src/figure.c ./src/element.c ./src/figure_list.c -l cmocka -o ./bin/tests && ./bin/tests