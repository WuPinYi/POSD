.PHONY: clean

all: clean dict bin/hw8

bin/hw8: src/tree_test.cpp src/tree_test.h src/tree_frame.h src/node_model.h src/subject.h src/observer.h src/node.h src/file.h src/folder.h src/link.h src/node_iterator.h src/null_iterator.h src/node_builder.h
	g++ -std=c++11 $< `wx-config --libs` `wx-config --cxxflags` -o $@ -lpthread

bin/hw7: test/ut_fs.cpp test/ut_fs.h src/node.h src/file.h src/folder.h src/link.h src/node_iterator.h src/null_iterator.h src/node_builder.h src/node_visitor.h obj/find_node_by_pathname_visitor.o obj/find_link_visitor.o obj/find_visitor.o obj/info_content_visitor.o
ifeq ($(OS), Windows_NT)
	g++ -std=c++11 obj/find_node_by_pathname_visitor.o obj/find_link_visitor.o obj/find_visitor.o obj/info_content_visitor.o $< -o $@ -lgtest
else
	g++ -std=c++11 obj/find_node_by_pathname_visitor.o obj/find_link_visitor.o obj/find_visitor.o obj/info_content_visitor.o $< -o $@ -lgtest -lpthread
endif

obj/find_node_by_pathname_visitor.o: src/find_node_by_pathname_visitor.cpp src/find_node_by_pathname_visitor.h
ifeq ($(OS), Windows_NT)
	g++ -std=c++11 -c $< -o $@ -lgtest
else
	g++ -std=c++11 -c $< -o $@ -lgtest -lpthread
endif

obj/find_link_visitor.o: src/find_link_visitor.cpp src/find_link_visitor.h
ifeq ($(OS), Windows_NT)
	g++ -std=c++11 -c $< -o $@ -lgtest
else
	g++ -std=c++11 -c $< -o $@ -lgtest -lpthread
endif

obj/find_visitor.o: src/find_visitor.cpp src/find_visitor.h
ifeq ($(OS), Windows_NT)
	g++ -std=c++11 -c $< -o $@ -lgtest
else
	g++ -std=c++11 -c $< -o $@ -lgtest -lpthread
endif

obj/info_content_visitor.o: src/info_content_visitor.cpp src/info_content_visitor.h
ifeq ($(OS), Windows_NT)
	g++ -std=c++11 -c $< -o $@ -lgtest
else
	g++ -std=c++11 -c $< -o $@ -lgtest -lpthread
endif

dict:
	mkdir -p bin obj

clean:
	rm -f bin/*
	rm -f obj/*
