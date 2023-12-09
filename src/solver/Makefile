CPP_VER = c++20
FLAGS = -I ../../include -O2 -std=$(CPP_VER)
SRC := $(wildcard *.cc)

.PHONY: all

all: $(SRC)
	g++ -c $^ $(FLAGS)