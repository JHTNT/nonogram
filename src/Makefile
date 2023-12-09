CPP_VER = c++20
FLAGS = -I ../include -O2 -std=$(CPP_VER)

.PHONY: all solver

all: nonogram

nonogram: solver
	mkdir -p ../bin
	g++ -o ../bin/nonogram $(FLAGS) nonogram.cpp */*.o

solver:
	$(MAKE) -C solver