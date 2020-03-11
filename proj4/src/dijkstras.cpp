// dijsktras.cpp
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>

using namespace std;
// Main Execution

class graph_Node{
	public:
		int x; 
		int y;
		int distance_from_start;
		map <int, char> neighbor;
		graph_Node* prev;
};

int main(int argc, char *argv[]) {
    
	int num_tiles = 0, point = 0, start_x = 0, start_y = 0, finish_x = 0, finish_y = 0;
	char tile = ' ',  map_tile = ' ';
	int map_row = 0, map_col = 0;
	map <char, int> tile_points;
	vector < vector <int> >my_map;
	vector < vector <graph_Node*> >my_graph;
	map <int, char>::iterator neighbor_it;
	multimap <int, int> distance_map;
	multimap <int, int>::iterator distance_it;
	set <int>::iterator path_it;
	set <int> path;
	int x_y = 0; 
	int cur_xy = 0;
	int temp_count = 0;
	set <string> graph_route;
	graph_Node * cur_node;
	
	cin>>num_tiles;
	while(temp_count < num_tiles){
		cin>>tile>>point;
		tile_points.insert(pair<char, int>(tile, point));
		temp_count++;
	}

	cin>>map_row>>map_col;
	my_map.resize(map_row);
	for(int i = 0; i < int(my_map.size()); i++){
		my_map[i].resize(map_col);
		for(int j = 0; j < int(my_map[i].size()); j++){
			cin>>map_tile;
			my_map[i][j] = map_tile;
		}
	}

	cin>>start_x>>start_y;
	cin>>finish_x>>finish_y;

	my_graph.resize(my_map.size());
	for(int i = 0; i < int(my_map.size()); i++){
		my_graph[i].resize(my_map[i].size());
		for(int j = 0; j < int(my_map[i].size()); j++){	
			graph_Node *temp_node = new graph_Node();
			temp_node->x = i;
			temp_node->y = j;
			temp_node->distance_from_start = 10000000; 
			if(i+1 < int(my_map[i].size())){
				x_y  = (i+1)*map_col+(j);
				temp_node->neighbor.insert(pair<int, char>(x_y, my_map[i+1][j]));
			}
			if(i-1 >= 0){
				x_y = (i-1)*map_col+(j);
				temp_node->neighbor.insert(pair<int, char>(x_y, my_map[i-1][j]));
			}
			if(j-1 >= 0){
				x_y = (i)*map_col+(j-1);
				temp_node->neighbor.insert(pair<int, char>(x_y, my_map[i][j-1]));
			}
			if(j+1 < int(my_map.size())){
				x_y = (i)*map_col + (j+1);
				temp_node->neighbor.insert(pair<int, char>(x_y, my_map[i][j+1]));
			}
			my_graph[i][j] = temp_node;
		}
	}

	cur_xy = (start_x)*map_col +(start_y);
	graph_route.insert(to_string(cur_xy));

	cur_node = my_graph[cur_xy/map_col][cur_xy%map_col];
	cur_node->distance_from_start = 0;
	
	distance_map.insert(pair<int, int>(0, cur_xy));

	cur_node->prev = NULL;

	while(int(graph_route.size()) != map_row*map_col){
		//cout<<graph_route.size()<<endl;
		for(neighbor_it = cur_node->neighbor.begin(); neighbor_it != cur_node->neighbor.end(); neighbor_it++){
			if(my_graph[neighbor_it->first/map_col][neighbor_it->first%map_col]->distance_from_start > (cur_node->distance_from_start + tile_points[my_map[cur_node->x][cur_node->y]])){
				my_graph[neighbor_it->first/map_col][neighbor_it->first%map_col]->distance_from_start = (cur_node->distance_from_start + tile_points[my_map[cur_node->x][cur_node->y]]);
				my_graph[neighbor_it->first/map_col][neighbor_it->first%map_col]->prev = cur_node;
				//my_graph[neighbor_it->first/map_col][neighbor_it->first%map_col]->path.insert((neighbor_it->first));
				distance_map.insert(pair<int, int>(my_graph[neighbor_it->first/map_col][neighbor_it->first%map_col]->distance_from_start, neighbor_it->first));
			}
		}

		distance_it = distance_map.begin();	
		while(graph_route.find(to_string(distance_it->second)) != graph_route.end()){
			distance_map.erase(distance_it);
			distance_it = distance_map.begin();
		}
		
		graph_route.insert(to_string(distance_it->second));
		cur_xy = distance_it->second;
		distance_map.erase(distance_it);
		cur_node = my_graph[cur_xy/map_col][cur_xy%map_col];
	}

	cout<<my_graph[finish_x][finish_y]->distance_from_start<<endl;
	cur_node = my_graph[finish_x][finish_y];

	while(cur_node != NULL){
		path.insert(cur_node->x*map_col+cur_node->y);
		cur_node = cur_node->prev;
	}

	path_it = path.begin();

	while(path_it != path.end()){
		cout<<(*path_it)/map_col<<" "<<(*path_it)%map_col<<endl;
		path_it++;
	}

	for(int i = 0; i < int(my_map.size()); i++){
		for(int j = 0; j < int(my_map[i].size()); j++){	
			delete my_graph[i][j];
		}
	}
	my_graph.clear();
	my_map.clear();
	distance_map.clear();

	return 0;
}

