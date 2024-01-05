TEST_SOURCES= ./tests/main.c \
 		 	  ./src/figure.c \
 	 	 	  ./src/element.c \
 	 	 	  ./src/figure_list.c \
 	  	 	  ./src/game.c

TEST_FAKES= ./tests/fakes/SDL.c

APP_SOURCES=  ./src/main.c \
 		 	  ./src/figure.c \
 	 	 	  ./src/element.c \
 	 	 	  ./src/figure_list.c \
 	  	 	  ./src/game.c \
 	  	 	  ./src/graphics.c \
 	  	 	  ./src/event.c

clear-tests:
	@[ -f './bin/tests' ] && rm './bin/tests' || true
clear-tetris:
	@[ -f './bin/tetris' ] && rm './bin/tetris' || true
clear:clear-tests clear-tetris
test: clear-tests
	gcc ${TEST_FAKES} ${TEST_SOURCES} -l cmocka -o ./bin/tests && ./bin/tests
build: clear-tetris
	gcc ${APP_SOURCES} $$(pkg-config --cflags --libs sdl2 SDL2_ttf) -o ./bin/tetris
run:
	./bin/tetris
bar: build run
all: clear test build run