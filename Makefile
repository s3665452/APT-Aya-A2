.default: all

all: a2

clean:
	rm -f a2 *.o

a2: Player.o main.o Tile.o LinkedList.o Node.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^