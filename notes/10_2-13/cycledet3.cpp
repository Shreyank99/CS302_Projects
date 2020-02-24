#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <stdlib.h>
using namespace std;

class Node 
{
  public:
    int id;
    vector <int> edges;
    int visited;
};

class Graph
{
  public:
    vector <Node *> nodes;
    void Print();
    int is_cycle(int index, int from);
};

int Graph::is_cycle(int index, int from)
{
  Node *n;
  int i;
  int rv;

  n = nodes[index];
  if (n->visited) {
    n->visited = 2;
    cout << "Cycle: " << index;
    return 1;
  }
  n->visited = 1;
  for (i = 0; i < n->edges.size(); i++) {
    if (n->edges[i] != from) {
      if (is_cycle(n->edges[i], index)) {
        cout << " " << index;
        if (n->visited == 2) {
          cout << endl;
          exit(1);
        }
        return 1;
      }
    }
  }
  return 0;
}

void Graph::Print()
{
  int i, j;
  Node *n;

  for (i = 0; i < nodes.size(); i++) {
    n = nodes[i];
    cout << "Node " << i << ": " << n->visited << ":";
    for (j = 0; j < n->edges.size(); j++) {
      cout << " " << n->edges[j];
    }
    cout << endl;
  }
}


int main(int argc, char **argv)
{
  Graph g;
  string s;
  int nn, n1, n2, i, c;
  Node *n;

  cin >> s;
  if (s != "NNODES") { cerr << "Bad graph\n"; exit(1); }
  cin >> nn;

  for (i = 0; i < nn; i++) {
    n = new Node;
    n->visited = 0;
    n->id = i;
    g.nodes.push_back(n);
  }

  while (!cin.fail()) {
    cin >> s >> n1 >> n2;
    if (!cin.fail()) {
      if (s != "EDGE") { cerr << "Bad graph\n"; exit(1); }
      g.nodes[n1]->edges.push_back(n2);
      g.nodes[n2]->edges.push_back(n1);
    }
  }

  c = 0;
  for (i = 0; i < g.nodes.size(); i++) {
    if (!g.nodes[i]->visited) {
      if (g.is_cycle(i, -1)) {
        cout << "There is a cycle reachable from node " << i << endl;
      }
    }
  }

  g.Print();
  return 0;
}
