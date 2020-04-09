#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <string>
#include "disjoint.h"

using namespace std;

#define talloc(type, num) (type *) malloc(sizeof(type)*(num))

class Superball {
  public:
    Superball(int argc, char **argv);
    int r;
    int c;
    int mss;
    int empty;
    vector <int> board;
    vector <int> goals;
    vector <int> colors;
};
void analyze_board(Superball* s, vector<string> &suggestion, DisjointSetByRankWPC &my_dset);
void analyze_strategy(Superball* s, vector<string> &strag, DisjointSetByRankWPC &my_dset);
void closest_goal_cell(Superball* s, DisjointSetByRankWPC &my_dset, int index ,map<int, string> &my_map);

void usage(const char *s) 
{
  fprintf(stderr, "usage: sb-play rows cols min-score-size colors\n");
  if (s != NULL) fprintf(stderr, "%s\n", s);
  exit(1);
}

Superball::Superball(int argc, char **argv)
{
  int i, j;
  string s;

  if (argc != 5) usage(NULL);

  if (sscanf(argv[1], "%d", &r) == 0 || r <= 0) usage("Bad rows");
  if (sscanf(argv[2], "%d", &c) == 0 || c <= 0) usage("Bad cols");
  if (sscanf(argv[3], "%d", &mss) == 0 || mss <= 0) usage("Bad min-score-size");

  colors.resize(256, 0);

  for (i = 0; i < strlen(argv[4]); i++) {
    if (!isalpha(argv[4][i])) usage("Colors must be distinct letters");
    if (!islower(argv[4][i])) usage("Colors must be lowercase letters");
    if (colors[argv[4][i]] != 0) usage("Duplicate color");
    colors[argv[4][i]] = 2+i;
    colors[toupper(argv[4][i])] = 2+i;
  }

  board.resize(r*c);
  goals.resize(r*c, 0);

  empty = 0;

  for (i = 0; i < r; i++) {
    if (!(cin >> s)) {
      fprintf(stderr, "Bad board: not enough rows on standard input\n");
      exit(1);
    }
    if (s.size() != c) {
      fprintf(stderr, "Bad board on row %d - wrong number of characters.\n", i);
      exit(1);
    }
    for (j = 0; j < c; j++) {
      if (s[j] != '*' && s[j] != '.' && colors[s[j]] == 0) {
        fprintf(stderr, "Bad board row %d - bad character %c.\n", i, s[j]);
        exit(1);
      }
      board[i*c+j] = s[j];
      if (board[i*c+j] == '.') empty++;
      if (board[i*c+j] == '*') empty++;
      if (isupper(board[i*c+j]) || board[i*c+j] == '*') {
        goals[i*c+j] = 1;
        board[i*c+j] = tolower(board[i*c+j]);
      }
    }
  }
}

main(int argc, char **argv)
{
	Superball *s;
	s = new Superball(argc, argv);
	vector <string> analyze_suggest; 
	vector <string> analyze_strag;

	DisjointSetByRankWPC *my_dset = new DisjointSetByRankWPC(int(s->board.size()));
	analyze_board(s, analyze_suggest, *my_dset);
	analyze_strategy(s, analyze_strag, *my_dset);
	int i, j, size; 
	int collect_i = 0, collect_j = 0;
	int cur_points = 0; 
	char temp;
	char color; 
	int cell1 = -1, cell2 = -1;
	srand(100000);
	stringstream ss;
	
	//No more suggestion
	if(analyze_suggest.size() == 0){
		for(int k = 0; k < int(s->goals.size()); k++){
			if(s->goals[k] != 0 && s->goals[k] != '.' && s->goals[k] != '*'){
				int count = 0;
				int next_elements = k+1;
				while(s->board[next_elements] == s->board[k] || next_elements% s->c == k%s->c){
					count++;
					next_elements++;
				}
				if(cur_points < count*s->colors[k]){
				cur_points = count*s->colors[k];
					collect_i = k/s->c;
					collect_j = k%s->c;
				}
				//Check left elements of goal
				next_elements = k;
				count = 0;
				while(s->board[next_elements] == s->board[k] || next_elements% s->c == k%s->c){
					next_elements--;
					count++;
				}
				if(cur_points < count*s->colors[k]){
					cur_points = count*s->colors[k];
					collect_i = k/s->c;
					collect_j = k%s->c;
				}
				
				//Check up elements of goal
				next_elements = k - s->c;
				count = 0;
				while(s->board[next_elements] == s->board[k] || next_elements >= 0){
					next_elements = next_elements - s->c;
					count++;
				}
				if(cur_points < count*s->colors[k]){
					cur_points = count*s->colors[k];
					collect_i = k/s->c;
					collect_j = k%s->c;
				}
				
				//Check down elements of goal
				next_elements = k + s->c;
				count = 0;
				while(s->board[next_elements] == s->board[k] || next_elements < s->board.size()){
					next_elements = next_elements - s->c;
					count++;
				}
				if(cur_points < count*s->colors[k]){
					cur_points = count*s->colors[k];
					collect_i = k/s->c;
					collect_j = k%s->c;
				}
			}
		}
		if(collect_i == 0 && collect_j == 0){
			int rand = 0;
			while(cell1 == -1 || cell2 == -1){
				if(s->board[rand] != '.' && s->board[rand] != '*'){	
					if(cell1 == -1){
						cell1 = rand;
						continue;
					}
					if(cell2 == -1 && s->board[cell1] != s->board[rand]){
						cell2 = rand;
						break;
					}
				}
				rand++;
			}
			cout<<"SWAP "<<cell1/s->c<<" "<<cell1%s->c<<" "<<cell2/s->c<<" "<<cell2%s->c<<endl;
			return 0;
		}

		int goal_index = collect_i*s->c+collect_j;
		int color_goal = s->board[goal_index];
		int match_color = 0;
		int swap_neighbor = 0;
		//Find same color on board
		for(int i =0; i < s->board.size(); i++){
			if(s->board[i] == color_goal && goal_index != i && my_dset->Find(i) == -1){
				match_color = i;
				i = s->board.size();
			}
		}
		int temp = goal_index;
		while(s->board[temp] == s->board[goal_index]){
			temp++;
		}

		swap_neighbor = temp;
		cell1 = match_color;
		cell2 = swap_neighbor;
		cout<<"SWAP "<<cell1/s->c<<" "<<cell1%s->c<<" "<<cell2/s->c<<" "<<cell2%s->c<<endl;
		return 0;
	}
	else if(s->empty > 5){
		//Collect biggest size in suggestion 
		for(int k =0 ; k < analyze_suggest.size(); k++){
			ss<<analyze_suggest[k];
			ss>>size>>color>>i>>temp>>j;
			//cout<<size<<" "<<color<<" "<<i<<" "<<j<<endl;
			if(cur_points < size*s->colors[color]){
				cur_points = size*s->colors[color];
				collect_i = i;
				collect_j = j;
			}
			ss.clear();
		}
		cout<<"SCORE "<<collect_i<<" "<<collect_j<<endl;
		return 0;
	}
	else{
		


	}
}

void analyze_board(Superball* s, vector<string> &suggestion, DisjointSetByRankWPC &my_dset){

  int row, col;
  char color;
  string suggest = "";
  for(int i = 0; i < s->r*s->c; i++){

      if(s->board[i] == '*' || s->board[i] == '.')  continue;

    //Check to union with left element
      if(i-1 >= 0){
        if(tolower(char(s->board[i])) == tolower(char(s->board[i-1])) && i%s->c != 0){
            if(my_dset.Find(i-1) == my_dset.Find(i))  continue;
            my_dset.Find(my_dset.Union(my_dset.Find(i), my_dset.Find(i-1)));
        }
      }
    //Check to union with right element
      if(i+1 < int(s->board.size())){
        if(tolower(char(s->board[i])) == tolower(char(s->board[i+1])) && i%s->c != (s->c)-1){
            if(my_dset.Find(i+1) == my_dset.Find(i))  continue;
            my_dset.Find(my_dset.Union(my_dset.Find(i), my_dset.Find(i+1)));
        }
      }
      //Top
      if(i-s->c >= 0){
        if(tolower(char(s->board[i])) == tolower(char(s->board[i-s->c]))){
            if(my_dset.Find(i) == my_dset.Find(i-s->c))   continue;
            my_dset.Find(my_dset.Union(my_dset.Find(i), my_dset.Find(i-s->c)));
        }
      }
      //Bottom
      if(i+s->c < int(s->board.size())){
        if(tolower(char(s->board[i])) == tolower(char(s->board[i+s->c]))){
            if(my_dset.Find(i) == my_dset.Find(i+s->c))   continue;
            my_dset.Find(my_dset.Union(my_dset.Find(i), my_dset.Find(i+s->c)));
        }
      }
  }

  for(int i = 0; i < s->r*s->c; i++){
    my_dset.Find(i);
  }

  map <int, int> goal_cell;
  map <int, int>::iterator goal_it;
  for(int i = 0; i < int(s->goals.size()); i++){ 
        if(s->goals[i] == 1){
			if(my_dset.Find(i) != -1 && goal_cell.find(my_dset.Find(i)) == goal_cell.end()){
				goal_cell.insert(pair<int, int>(my_dset.Find(i), i));
			}
		}
  }

  for(goal_it = goal_cell.begin(); goal_it != goal_cell.end(); goal_it++){
      int count = 0;
      if(s->board[goal_it->first] == '*')   continue;
      for(int i = 0; i < int(s->board.size()); i++){
          if(my_dset.Find(i) == goal_it->first){
            count++;
        }
      }

      if(count >= s->mss){
		  row = (goal_it->second)/(s->c);
		  col = (goal_it->second)%(s->c);
		  color = char(s->board[goal_it->first]);
		  
		  suggest = "" + to_string(count)+ " " +(color) + " " +to_string(row)+","+to_string(col);
		  suggestion.push_back(suggest);
      }
  }

}
void analyze_strategy(Superball* s, vector<string> &strag, DisjointSetByRankWPC &my_dset){	
  map <int, int> potent_cell;
  map <int, int>::iterator potent_it;
  int row, col;
  char color;
  string strategy;
  for(int i = 0; i < int(s->goals.size()); i++){ 
		if(my_dset.Find(i) != -1 && potent_cell.find(my_dset.Find(i)) == potent_cell.end()){
			potent_cell.insert(pair<int, int>(my_dset.Find(i), 1));
		}
		else if(my_dset.Find(i) != -1){
			//increase count
			potent_cell.at(my_dset.Find(i)) += 1;
		}
  }
  for(potent_it = potent_cell.begin(); potent_it != potent_cell.end(); potent_it++){
	if(potent_cell[potent_it->first] >= s->mss){
		row = potent_it->first/(s->c);		
		col = potent_it->first%(s->c);
		color = char(s->board[potent_it->first]);
		strategy = "" + to_string(potent_it->second)+ " " +(color) + " " +to_string(row)+","+to_string(col);
		strag.push_back(strategy);
	}
  }
}

void closest_goal_cell(Superball* s, DisjointSetByRankWPC &my_dset, int index ,map<int, string> &my_map){
	
	int temp_index;
	int count;
	//Assign realitively big number
	int closest_goal = s->c;
	for(int i = 0; i < s->goals.size(); i++){
		if(s->goals[i] == 1 && s->board[i] != '*'){
			//cout<<i<<" -> "<<i%s->c<<" = "<<s->c-1<<endl;
			if(i%s->c == 0 || i%s->c == (s->c) -1)	continue;	
			//cout<<i<<" -> "<<i%s->c<<" = "<<s->c-1<<endl;

			if(s->board[index] == s->board[i]) count = 0;
			else	count = 1;

			if((i)%s->c == 0 || i%s->c == 1){

				temp_index = i+1%s->c;
				while(temp_index < s->c && my_dset.Find(temp_index) != my_dset.Find(index) && s->goals[temp_index] != 1){
					count++;
					temp_index++;
				}
				if(count < closest_goal && count < s->empty){
					closest_goal = count;
					my_map.clear();
					my_map.insert(pair<int, string>(i, "RIGHT"));

				}
			}
			else if((i)%s->c == (s->c)-1 || i%s->c == (s->c)){
				temp_index = i-1;
				while(temp_index > 0 && my_dset.Find(temp_index) != my_dset.Find(index)){
					count++;
					temp_index--;
				}
				
				if(count < closest_goal && count < s->empty){
					closest_goal = count;
					my_map.clear();
					my_map.insert(pair<int, string>(i, "LEFT"));
				}
			}
		}
	}
	if(my_map.empty()){
		my_map.insert(pair<int, string>(-1, "TOO EARLY"));
	}
}
