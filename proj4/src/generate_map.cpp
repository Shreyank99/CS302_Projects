// generate_map.cpp
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>

using namespace std;
// Main Execution

int main(int argc, char *argv[]) {
	
	if(argc < 2){
		cerr<<"Not enough arguments provided"<<endl;
		return 0; 
	}
	int graph_size = atoi(argv[1]);
	int rand_num; 
	string filename = "graph_map_" + to_string(graph_size) + ".txt";
	vector<char> map_char = {'f', 'g', 'G', 'h', 'm', 'r'};
	//cout<<filename<<endl;
	ofstream fs;
	fs.open(filename.c_str());
	
	if((fs.fail())){
		cerr<<"Could not open file";
		return 0;
	}

	fs<<"6"<<endl;
	fs<<"f 3"<<endl;
	fs<<"g 1"<<endl;
	fs<<"G 2"<<endl;
	fs<<"h 4"<<endl;
	fs<<"m 7"<<endl;
	fs<<"r 5"<<endl;
	fs<<graph_size<<" "<<graph_size<<endl;
	
	for(int i = 0; i < graph_size; i++){
		for(int j = 0; j < graph_size; j++){
			rand_num = rand() % 6;
			fs<<map_char[rand_num]<<" ";
		}
		fs<<endl;
	}
	fs<<"0 0"<<endl;
	fs<<graph_size-1<<" "<<graph_size-1<<endl;
	fs.close();
	return 0;
}

