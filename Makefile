SYS := $(shell gcc -dumpmachine)

all: sfml-starfield

clean:
	rm *o sfml-starfield

ifneq (, $(findstring linux, $(SYS)))
sfml-starfield: main.o
	g++ -std=c++11 main.o -o sfml-starfield -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
	g++ -std=c++11 -c main.cpp
endif

ifneq (, $(findstring darwin, $(SYS)))
sfml-starfield: main.o
	g++ -std=c++11 main.o -o sfml-starfield -lsfml-graphics -lsfml-window -lsfml-system -I/usr/local/include -L/usr/local/lib

main.o: main.cpp
	g++ -std=c++11 -c main.cpp -I/usr/local/include
endif
