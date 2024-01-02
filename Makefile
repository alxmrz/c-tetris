build:
	gcc ./src/main.c ./src/figure.c ./src/element.c $$(pkg-config --cflags --libs sdl2) -o ./bin/tetris && ./bin/tetris
test:
	gcc ./tests/main.c ./src/figure.c ./src/element.c -l cmocka -o ./bin/tests && ./bin/tests