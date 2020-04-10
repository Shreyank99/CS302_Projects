#include <cstdio>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std; 
typedef enum {Source, Sink, Dice, Word}Node_type;


/*
	Class Definitions
*/

class Edge{
	public:
		class Node *to;
		class Node *from;
		Edge *reverse;
		int original;
		int residual;
		int index; 
};

class Node{
	public:
		int id;
		Node_type type;
		vector <bool> letters;
		int visited;
		vector <Edge *>adj;
		Edge *backedge;
};

class Graph{
	public:
		vector <Node *> nodes;
		int BFS();
		int canIspell();
		vector <int> spelling_id;
		void Delete_halfGraph();
		int minnodes;
};


/*
	Graph Functions
*/

int Graph::BFS(){
	vector <Node *> queue;		//hold queue of nodes to check
	vector <int> visited;		//hold queue of visited node ids
	queue.push_back(nodes[0]);	//start with beginning node
	
	//run while there is something in queue
	while(!queue.empty()){
		Node* curr = queue[0];		//get first element of queue
		queue.erase(queue.begin());	//remove first element from queue
		
		if(curr->type == Sink)		//return if this is target
			return 1;
			
		//run through adj list
		for(int i = 0; i < int(curr->adj.size()); i++){
			Edge *thisEdge = curr->adj[i];		//edge we are looking at
			Node *thisNode = thisEdge->to;		//to node we are looking at
			int thisId = thisNode->id;			//nodes id
			
			//make sure original is 1 and we have not visited this node
			if(thisEdge->original == 1 && !count(visited.begin(), visited.end(), thisId)){
				visited.push_back(thisId);					//record node as visited
				thisNode->backedge = thisEdge->reverse;		//set nodes backedge
				queue.push_back(thisNode);					//add node to queue
			}
		}
	}
	
	//if here, no path found
	return 0;
}


/*
	Main Execution
*/

int main(int argc, char* argv[]){
	
	//Check if two file names are provided
	if(argc != 3){
		cerr<<"Not enough arguements provided"<<endl;
		return 0;
	}

	
	string dice_filename;
	string line;
	int id = 0;
	ifstream dice_fin;
	
	//Set up source node to be used later
	Node *source_node = new Node();
	source_node->id = id;
	id++;
	source_node->type = Source;
	source_node->visited = 0;
	source_node->letters.resize(26, 0);
	source_node->backedge = NULL;

	dice_filename = argv[1];
	dice_fin.open(dice_filename.c_str());

	if(dice_fin.fail()){
		cerr<<"Could not open file"<<endl;
		return 0; 
	}
	
	int index_source = 0;	//to keep track of all edges to soruce;

	//Read all the dice and make edges to source node
	while(getline(dice_fin, line)){
		Node *dice_node = new Node();
		dice_node->id = id;
		id++;
		dice_node->type = Dice;
		dice_node->visited = 0;
		dice_node->letters.resize(26, 0);
		
		for(char &letter: line){
			int num_letter = letter - 65;
			dice_node->letters[num_letter] = 1;
		}
		
		Edge *to_source = new Edge();
		Edge *from_source = new Edge();

		to_source->from = dice_node;
		to_source->to = source_node;
		to_source->original = 1;
		to_source->residual = 0;
		to_source->index = 0;

		from_source->from = source_node;
		from_source->to = dice_node;
		from_source->original = 1;
		from_source->residual = 0;
		from_source->index = index_source;
		index_source++;
	
		from_source->reverse = to_source;
		to_source->reverse = from_source;
		
		//push back new edge connections into adj list of node
		dice_node->adj.push_back(to_source);
		source_node->adj.push_back(from_source);
		
		//backedge = edge that got you to that node
		dice_node->backedge = from_source;
	}
	
	/*
	 *To do 
	 * 1. read in the word and make a node out of the letter
	 * 2. make connection between word and dice nodes 
	 * 3. make connection between word and sink node
	 * 4. other stuff :(
	 *
	 *
	 *
	 */

	return 0;
}
