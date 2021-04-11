.PHONY: clean mkdir
BIN=bin
SRC=src
TEST=test
OBJ=obj
all: clean mkdir $(BIN)/ut_all $(OBJ)
$(BIN)/ut_all:  $(TEST)/ut_main.cpp $(TEST)/ut_fs.h $(SRC)/link.h $(SRC)/file.h $(SRC)/folder.h $(SRC)/node.h $(SRC)/iterator.h $(SRC)/null_iterator.h $(SRC)/visitor.h obj/filesystem_builder.o
		g++ -std=c++11 -Wfatal-errors -o $(BIN)/ut_all $(TEST)/ut_main.cpp obj/filesystem_builder.o -lgtest -lpthread

obj/filesystem_builder.o: src/filesystem_builder.cpp src/filesystem_builder.h
	g++ -std=c++11 -Wfatal-errors -c src/filesystem_builder.cpp -o obj/filesystem_builder.o
$(OBJ):obj/filesystem_builder.o 
clean: 
		rm -f $(BIN)/* 
		rm -f $(OBJ)/*
mkdir:
		mkdir -p $(BIN)
		mkdir -p $(OBJ)