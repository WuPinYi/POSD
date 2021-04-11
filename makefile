.PHONY: clean mkdir
BIN=bin
SRC=src
TEST=test

all: clean mkdir hw4 
hw4:  $(TEST)/ut_main.cpp $(TEST)/ut_node.h $(SRC)/file.h $(SRC)/folder.h $(SRC)/node.h 
		g++ -std=c++11 -Wfatal-errors $(TEST)/ut_main.cpp -o $(BIN)/ut_all  -lgtest -lpthread

clean:
		rm -f $(BIN)/* 
mkdir:
		mkdir -p $(BIN)
