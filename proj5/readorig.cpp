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
	string word_filename;
	string line;
	int id = 0;
	ifstream dice_fin;
	ifstream word_fin;
	
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
	word_filename = argv[2];

	if(dice_fin.fail()){
		cerr<<"Could not open file"<<endl;
		return 0; 
	}
	Graph *my_graph = new Graph();
	my_graph->nodes.push_back(source_node);
	my_graph->minnodes = 0;
	
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
		source_node->adj.push_back(from_source);
		
		//backedge = edge that got you to that node
		dice_node->backedge = from_source;
		my_graph->nodes.push_back(dice_node);
		my_graph->minnodes++;
	}
	
	dice_fin.close();
	//Open word file
	word_fin.open(word_filename.c_str());
	//check if it failed
	if(word_fin.fail()){
		cerr<<"Cannot open word file"<<endl;
		return 0;
	}
	int num_dice = my_graph->minnodes;
	
	while(getline(word_fin, line)){			
		for(char &letter: line){
			int num_letter = letter - 65;
			Node *word_node = new Node();
			word_node->id = id;
			id++;
			word_node->type = Word;
			word_node->visited = 0;
			word_node->letters.resize(26, 0);
			word_node->letters[num_letter] = 1;
			
			//Word index = 0 because no prev connections
			int word_index = 0;
			
			//Dice index = 1 becuase already connected to source node
			int dice_index = 1;
	
			//Check all the dice nodes to make edges -- skip 0 because source node
			for(int i = 1; i <= num_dice; i++){
				//if Dice and word_node have the same letter, create an edge/connection
				if(my_graph->nodes[i]->letters[num_letter] == 1 && my_graph->nodes[i]->type == Dice){	
					Edge *to_word = new Edge();
					Edge *from_word = new Edge();

					to_word->from = my_graph->nodes[i];
					to_word->to = word_node;
					to_word->original = 1;
					to_word->residual = 0;
					to_word->index = word_index;
					word_index++;

					from_word->from = word_node;
					from_word->to = my_graph->nodes[i];
					from_word->original = 1;
					from_word->residual = 0;
					from_word->index = dice_index;
					dice_index++;
				
					from_word->reverse = to_word;
					to_word->reverse = from_word;
					
					//push back new edge connections into adj list of node
					my_graph->nodes[i]->adj.push_back(to_word);
					//word_node->adj.push_back(from_word);
					
				}
			}
			my_graph->nodes.push_back(word_node);
			my_graph->minnodes++;
		
		}
		
		//Set up sink node to be used later
		Node *sink_node = new Node();
		sink_node->id = id;
		id++;
		sink_node->type = Sink;
		sink_node->visited = 0;
		sink_node->letters.resize(26, 0);
		sink_node->backedge = NULL;
		
		int num_word = my_graph->minnodes;
		int sink_index = 0;
		//Make connection between word nodes and sink node
		for(int i = num_dice+1; i <= num_word; i++){
			Edge *to_sink = new Edge();
			Edge *from_sink = new Edge();

			to_sink->from = my_graph->nodes[i];
			to_sink->to = sink_node;
			to_sink->original = 1;
			to_sink->residual = 0;
			if(my_graph->nodes[i]->adj.size() == 0){
				to_sink->index = 0;
			}	
			else{
				to_sink->index = my_graph->nodes[i]->adj[my_graph->nodes[i]->adj.size()-1]->index+1;
			}
			
			from_sink->from = sink_node;
			from_sink->to = my_graph->nodes[i];
			from_sink->original = 1;
			from_sink->residual = 0;
			from_sink->index = sink_index;
			sink_index++;
			
			from_sink->reverse = to_sink;
			to_sink->reverse = from_sink;
			
			my_graph->nodes[i]->adj.push_back(to_sink);
		}

		my_graph->nodes.push_back(sink_node);
		my_graph->minnodes++;
		

		for(int i = 0; i < my_graph->nodes.size(); i++){
			cout<<"Node "<<my_graph->nodes[i]->id<<": "<<my_graph->nodes[i]->type<<" Edges to ";
			for(int j = 0; j < my_graph->nodes[i]->adj.size(); j++){
				cout<<my_graph->nodes[i]->adj[j]->to->id<<" ";
			}
			cout<<endl;
		}
		
		vector <Node *>::iterator nodes_it = my_graph->nodes.begin();

		//Delete all word nodes and edges between words and dices
		for(int i = 0; i < my_graph->nodes.size(); ){
			if(my_graph->nodes[i]->type == Dice){
				//Delete dice-word nodes connection		
				my_graph->nodes[i]->adj.clear();
				i++;
			}
			else if(my_graph->nodes[i]->type ==Word || my_graph->nodes[i]->type == Sink){
				delete my_graph->nodes[i];	
				my_graph->nodes.erase(nodes_it+i,nodes_it+(i+1));
			}
			else{
				i++;
			}
		}
		my_graph->minnodes = my_graph->nodes.size()-1;
		id = num_dice + 1;
		cout<<endl;
	}


	return 0;
}
