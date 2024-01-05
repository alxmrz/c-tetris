TEST_SOURCES= ./tests/main.c \
 		 	  ./src/figure.c \
 	 	 	  ./src/element.c \
 	 	 	  ./src/figure_list.c \
 	  	 	  ./src/game.c

APP_SOURCES=  ./src/main.c \
 		 	  ./src/figure.c \
 	 	 	  ./src/element.c \
 	 	 	  ./src/figure_list.c \
 	  	 	  ./src/game.c


test:
	gcc ${TEST_SOURCES} -l cmocka -o ./bin/tests && ./bin/tests
build:
	gcc ${APP_SOURCES} $$(pkg-config --cflags --libs sdl2 SDL2_ttf) -o ./bin/tetris
run:
	./bin/tetris
bar: build run
all: test build run