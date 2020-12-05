BIN_DIR=./bin

LIB=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
BIN=../bin
FLAGS=-Wall -ansi -std=c++17 -lstdc++fs -Wno-psabi

HEADER_TYPE=.h
SOURCE_TYPE=.cpp
BINARY_TYPE=.o

OBJETS=$(shell find ./ -type f -name "*.cpp")
HEADER=$(shell find ./ -type f -name "*.h")
BINS:=$(SRCS:$(SRC_DIR)%$(SOURCE_TYPE)=$(BIN_DIR)%$(BINARY_TYPE))

EXEC=cluedo

all: $(EXEC)

$(EXEC): $(BINS)
	g++ $^ -o $(EXEC) $(LIB) $(FLAGS)

$(BIN_DIR)/%$(BINARY_TYPE) : $(OBJETS)
	g++ $(CFLAGS) -c $< -o $(BIN_DIR)/$*$(BINARY_TYPE)

clear:
	@rm -f $(BIN_DIR)/*

mrproper: clear
	@rm -f $(EXEC)
