ALL = example 

all: $(ALL)

clean: 
	rm -f *.o a.out $(ALL)

OBJS = disjoint-height.o disjoint-rank.o disjoint-size.o

example.o: disjoint.h
disjoint-height.o: disjoint.h
disjoint-rank.o: disjoint.h
disjoint-size.o: disjoint.h

.SUFFIXES: .cpp .o 

.cpp.o: 
	g++ -c -O $*.cpp

example: example.o $(OBJS)
	g++ -O -o example example.o $(OBJS)

