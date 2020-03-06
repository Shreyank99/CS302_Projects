all: sb-play sb-read sb-analyze sb-play3

sb-play: sb-play.cpp
	g++ -std=c++11 -O3 -o sb-play sb-play.cpp disjoint-rank.cpp

sb-play3: sb-play3.cpp
	g++ -std=c++11 -O3 -o sb-play3 sb-play3.cpp disjoint-rank.cpp

sb-read: sb-read.cpp
	g++ -std=c++11 -O3 -o sb-read sb-read.cpp disjoint-rank.cpp

sb-analyze: sb-analyze.cpp
	g++ -std=c++11 -O3 -o sb-analyze sb-analyze.cpp disjoint-rank.cpp

.PHONY: clean
clean:
	rm -rf sb-play sb-read sb-analyze sb-play3
