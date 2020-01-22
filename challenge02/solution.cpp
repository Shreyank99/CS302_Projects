// Challenge 01: Rotating Arrays; null solution
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <stdlib.h>
#include <algorithm>
#include <iterator>
#include <utility>
using namespace std;
int main(int argc, char *argv[]){
		
		stringstream ss;
		string temp;
		int n_elements, element;
		vector <int> my_vec;
		multimap <int, pair< int, int > > my_map;
		multimap <int, pair< int, int > >::iterator map_it;
		int num1, num2, diff; 
		while(getline(cin, temp)){
			ss.clear();
			ss<<temp;
			ss>>n_elements;
			ss.clear();
			getline(cin, temp);
			ss<<temp;
			while(ss>>element){
				my_vec.push_back(element);
			}
			sort(my_vec.begin(), my_vec.end());

			for(int i = 0 ; i < int(my_vec.size()-1); i++){
				num1 = my_vec[i];
				num2 = my_vec[i+1];
				diff = abs(num1-num2);
				my_map.insert(pair<int, pair<int, int> > (diff, pair<int, int> (num1, num2)));
			}
				map_it = my_map.begin();
				int temp3 = map_it->first;
				while(temp3 == map_it->first){
					cout<<map_it->second.first<<" "<<map_it->second.second;
					map_it++;
					if(temp3 == map_it->first)	cout<<" ";
				}
				cout<<endl;
				my_vec.clear();
				my_map.clear();
		}
	return 0;
}

