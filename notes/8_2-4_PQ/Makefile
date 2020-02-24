CXX=		g++
CXXFLAGS=	-g -Wall -std=gnu++11
SHELL=		bash

all:		driver

driver:	pqueue_set.cpp pqueue_heap.cpp driver.cpp
	g++ -o $@ $^

clean:
	rm -f driver


