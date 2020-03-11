Project 04: Path Finding
========================

This project implements a [Dijkstra's Algorithm] to perform rudimentary path
finding on a 2D tile-based map.

[Dijkstra's Algorithm]: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm


Input
-----

    TILES_N
    TILE_NAME_0	TILE_COST_0
    ...
    TILE_NAME_N-1	TILE_COST_N-1

    MAP_ROWS MAP_COLUMNS
    TILE_0_0    ...
    ...

    TRAVELER_START_ROW TRAVELER_START_COL
    TRAVELER_END_ROW   TRAVELER_END_COL

Output
------

    Cost
    [(ROW_0, COL_0), ...]

Benchmark Test command
-----------------------
	
	time ./src/dijkstras < test_maps/graph_map_10.txt >/dev/null
	time ./src/dijkstras < test_maps/graph_map_20.txt >/dev/null
	time ./src/dijkstras < test_maps/graph_map_50.txt >/dev/null
	time ./src/dijkstras < test_maps/graph_map_100.txt >/dev/null
	time ./src/dijkstras < test_maps/graph_map_500.txt >/dev/null
	time ./src/dijkstras < test_maps/graph_map_1000.txt >/dev/null

Benchmark
---------
| N             | Elapsed Time  | Memory Usage   |
|---------------|---------------|----------------|
| 10            | 0.002         | 30970          |
| 20            | 0.003         | 124330         |
| 50            | 0.011         | 774019         |
| 100           | 0.038         | 3111801        |
| 200           | 0.161         | 12505890       |
| 500           | 1.108         | 78481208       |
| 1000          | 4.920         | 21111924004    |
|---------------|---------------|----------------|


Question
--------

	1. How did you represent the map as a graph?
		I created a class called graph_Node which contained all the information i needed to create a graph. The class contained information such as x and y position, neighbors, and prev node with the closest distance to the source. 
	2. What is complexity of your implementation of Dijkstra's Algorithm?
		My time complexity for my implementation of Dijkstra's Algorithm is O(n * log n) where n represents the number of verticles in the graph. I made a 2-D vector representation of the data where each element in the vector is a class called graph_Node. The graph_Node contains the position of the node, distance from the start and pointer to the previous node which is closest to the source node.
	3. How well does your implementation scale? 
		My implementation has a time complexity of O(n * log n)

