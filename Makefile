LIB=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
BIN=../bin
FLAGS=-Wall -ansi -std:c++11
EXEC=cluedo

OBJETS=$(shell find ./ -type f -name "*.cpp")
BINARIES=$(shell find ./ -type f -name "*.o")

all:
	g++ $(OBJETS) -o $(EXEC) $(LIB)
ifneq ($(BINARIES),)
	mv $(BINARIES) bin
endif

clean:
	find ../ -type f -name '*.o' -exec rm {} +
