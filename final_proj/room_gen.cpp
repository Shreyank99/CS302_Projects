#include <iostream>
#include <vector>
#include <cstdio>
#include "disjoint-rank.cpp"

using namespace std;

class Room{
	vector < vector <int> >room;
};

void room1_gen(vector < vector <int> > cur_room);
void room2_gen(vector < vector <int> > cur_room);
void room3_gen(vector < vector <int> > cur_room);
void room4_gen(vector < vector <int> > cur_room);
void room5_gen(vector < vector <int> > cur_room);
void room6_gen(vector < vector <int> > cur_room);
void room7_gen(vector < vector <int> > cur_room);
void room8_gen(vector < vector <int> > cur_room);
void room9_gen(vector < vector <int> > cur_room);
void room10_gen(vector < vector <int> > cur_room);
void room11_gen(vector < vector <int> > cur_room);
void room12_gen(vector < vector <int> > cur_room);
void room13_gen(vector < vector <int> > cur_room);
void room14_gen(vector < vector <int> > cur_room);
void room15_gen(vector < vector <int> > cur_room);
void room16_gen(vector < vector <int> > cur_room);

int main(){
	vector <int> temp_room_row(10, 0)
	vector < vector <int> >temp_room(10, temp_room_row);
	vector < Room >rooms;
	rooms.resize(16, temp_room);
	room1_gen(rooms[1]);
}

void room1_gen(vector < vector <int> >cur_room){
	

}

