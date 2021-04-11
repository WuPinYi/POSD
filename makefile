.PHONY: clean dirs

all: clean dirs bin/ut_all

bin/ut_all: test/ut_shape.cpp src/circular_sector.h src/ellipse.h src/triangle.h
	g++ -std=c++11 test/ut_shape.cpp -o bin/ut_all -lgtest -lpthread

dirs:
	mkdir -p bin

clean:
	rm -f bin/*