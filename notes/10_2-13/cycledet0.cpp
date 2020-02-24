#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <stdlib.h>
using namespace std;

class Node {
  public:
    int id;
    vector <int> edges;
    int visited;
};

class Graph {
  public:
    vector <Node *> nodes;
    void Print();
    int is_cycle(int index);
};

int Graph::is_cycle(int index)
{
  Node *n;
  int i;

  n = nodes[index];
  if (n->visited) return 1;
  n->visited = 1;
  for (i = 0; i < n->edges.size(); i++) {
    if (is_cycle(n->edges[i])) return 1;
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
  int nn, n1, n2, i;
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

  for (i = 0; i < g.nodes.size(); i++) {
    if (!g.nodes[i]->visited) {
      if (g.is_cycle(i)) {
        cout << "There is a cycle reachable from node " << i << endl;
      } else {
        cout << "No cycle reachable from node " << i << endl;
      }
    }
  }
  return 0;
}
