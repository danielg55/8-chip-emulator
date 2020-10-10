CXX       := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -g

BIN     := bin
SRC     := source.cpp
LIB		:= SDL2
EXECUTABLE  := main

all: $(EXECUTABLE)

run: all
	clear
	./$(EXECUTABLE) 10 3 tetris.ch8

$(EXECUTABLE): $(SRC)
	$(CXX) $(CXX_FLAGS) $^ -l$(LIB) -o $@
