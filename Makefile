#
# A simple makefile for compiling a c++ project
#
SRC=./src
TARGET=./target
GCC = g++
CFLAGS = -o $(TARGET)/main.out
ARGS = 101
RM = rm -rf

run: main.o  ugraph.o 
	g++ -o run main.o  ugraph.o 
ugraph.o: ugraph.cpp ugraph.h  timestamp.h
	g++ -c -Wall -pedantic -g -std=c++11 ugraph.cpp
main.o: main.cpp  ugraph.h 
	g++ -c -Wall -pedantic -g -std=c++11 main.cpp
clean: 
	rm main.o ugraph.o run
