.PHONY: clean mkdir
BIN=bin
SRC=src
TEST=test
OBJ=obj
all: clean mkdir $(BIN)/ut_all $(OBJ)
$(BIN)/ut_all:  $(TEST)/ut_main.cpp $(TEST)/ut_fs.h $(SRC)/file.h $(SRC)/folder.h $(SRC)/node.h $(SRC)/iterator.h $(SRC)/null_iterator.h $(SRC)/link.h $(SRC)/visitor.h obj/update_path_visitor.o obj/find_visitor.o
		g++ -std=c++11 -Wfatal-errors -o $(BIN)/ut_all $(TEST)/ut_main.cpp obj/update_path_visitor.o obj/find_visitor.o -lgtest -lpthread

obj/update_path_visitor.o: src/update_path_visitor.cpp src/update_path_visitor.h
	g++ -std=c++11 -Wfatal-errors -c src/update_path_visitor.cpp -o obj/update_path_visitor.o
obj/find_visitor.o: src/find_visitor.cpp src/find_visitor.h
	g++ -std=c++11 -Wfatal-errors -c src/find_visitor.cpp -o obj/find_visitor.o
$(OBJ):obj/update_path_visitor.o obj/find_visitor.o
clean: 
		rm -f $(BIN)/* 
		rm -f $(OBJ)/*
mkdir:
		mkdir -p $(BIN)
		mkdir -p $(OBJ)