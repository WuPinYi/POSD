.PHONY: clean dirs

all: clean dirs bin/ut_all

bin/ut_all: src/main.cpp src/circular_sector.h src/ellipse.h src/triangle.h src/sort.h test/ut_sort.h
	g++ -std=c++11 -Wfatal-errors src/main.cpp -o bin/ut_all -lgtest -lpthread

dirs:
	mkdir -p bin

clean:
	rm -f bin/*