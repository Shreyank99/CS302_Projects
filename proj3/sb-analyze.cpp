#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <vector>
#include <map>
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

void analyze_board(Superball* s, vector<string> &suggestion);

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
  vector<string> suggestion;
  s = new Superball(argc, argv);
  analyze_board(s, suggestion);

}

void analyze_board(Superball* s, vector<string> &suggestion){
 
  DisjointSetByRankWPC *my_dset = new DisjointSetByRankWPC(int(s->board.size()));

  for(int i = 0; i < s->r*s->c; i++){
	
	  if(s->board[i] == '*' || s->board[i] == '.')	continue;
	  
	//Check to union with left element
	  if(i-1 >= 0){
		if(tolower(char(s->board[i])) == tolower(char(s->board[i-1]))){
			if(my_dset->Find(i-1) == my_dset->Find(i))	continue;
			my_dset->Find(my_dset->Union(my_dset->Find(i), my_dset->Find(i-1)));
		}
	  }
	//Check to union with right element
	  if(i+1 < int(s->board.size())){
		if(tolower(char(s->board[i])) == tolower(char(s->board[i+1]))){
			if(my_dset->Find(i+1) == my_dset->Find(i))	continue;
			my_dset->Find(my_dset->Union(my_dset->Find(i), my_dset->Find(i+1)));
		}
	  }
	  //Top
	  if(i-s->c >= 0){
		if(tolower(char(s->board[i])) == tolower(char(s->board[i-s->c]))){
			if(my_dset->Find(i) == my_dset->Find(i-s->c))	continue;
			my_dset->Find(my_dset->Union(my_dset->Find(i), my_dset->Find(i-s->c)));
		}
	  }
	  //Bottom
	  if(i+s->c < int(s->board.size())){
		if(tolower(char(s->board[i])) == tolower(char(s->board[i+s->c]))){
			if(my_dset->Find(i) == my_dset->Find(i+s->c))	continue;
			my_dset->Find(my_dset->Union(my_dset->Find(i), my_dset->Find(i+s->c)));
		}
	  }
  }
  
  for(int i = 0; i < s->r*s->c; i++){
	my_dset->Find(i);
  }
	
  map <int, int> goal_cell;
  map <int, int>::iterator goal_it;
  for(int i = 0; i < int(s->goals.size()); i++){
	if(s->goals[i] == 1){
		if(my_dset->Find(i) != -1 && goal_cell.find(my_dset->Find(i)) == goal_cell.end()){
			goal_cell.insert(pair<int, int>(my_dset->Find(i), i));
		}
	}
  }
	
//  cout<<"Scoring sets: "<<endl; 
  int scoring_Set = 0;
  for(goal_it = goal_cell.begin(); goal_it != goal_cell.end(); goal_it++){
	  int count = 0;
	  if(s->board[goal_it->first] == '*')	continue;
	  for(int i = 0; i < int(s->board.size()); i++){
		  if(my_dset->Find(i) == goal_it->first){
			count++;
		}
	  }
	  if(count >= s->mss){
		  if(scoring_Set == 0){
			scoring_Set = 1;
			cout<<"Scoring sets: "<<endl; 
		  }
		  cout<<"\tSize: "<<count<<" Char: "<<char(s->board[goal_it->first])<<" Scoring Cell: "<<(goal_it->second)/(s->c)<<","<<(goal_it->second)%(s->c)<<endl;
		  suggestion.push_back("\tSize: "+count /*+" Char: "+char(s->board[goal_it->first])+" Scoring Cell: "+(goal_it->second)/(s->c)+","+(goal_it->second)%(s->ci)*/);
	  }
  }
  delete my_dset;
}
