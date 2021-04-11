.PHONY: clean mkdir
BIN=bin
SRC=src
TEST=test

all: clean mkdir hw5 
hw5:  $(TEST)/ut_main.cpp $(TEST)/ut_fs.h $(SRC)/file.h $(SRC)/folder.h $(SRC)/node.h $(SRC)/iterator.h $(SRC)/null_iterator.h $(SRC)/utilities.h
		g++ -std=c++11 -Wfatal-errors $(TEST)/ut_main.cpp -o $(BIN)/ut_all  -lgtest -lpthread

clean:
		rm -f $(BIN)/* 
mkdir:
		mkdir -p $(BIN)

