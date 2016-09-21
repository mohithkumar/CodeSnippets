#ifndef BFS_GRAPHS_H
#define BFS_GRAPHS_H

#include <cstddef>

namespace
{
    const int END(-99999);
};

typedef unsigned int uint;
typedef struct Node* NodePtr;

struct Node
{
    int info;
    bool visited;
    Node* next;

  public:
    Node() : info(0), visited(false), next(NULL) {}
    Node(int i) : info(i), visited(false), next(NULL) {}

    ~Node() { info = 0; visited = false; next = NULL; }
};


class Graph
{
  public:
    Graph(uint size = 2);
    ~Graph();
    bool isGraphConnected();
    bool addEdge(int x, int y);
    bool removeEdge(int x, int y);
    void breadthFirstSearch(int start, int end);
    uint getNumberOfNodes() const { return currSize; }

   private:
    uint iterativeBreadthFirstSearch(int start, int end);

    uint maxSize; // Max Number of Nodes 
    uint currSize; // Curr Number of Nodes
    NodePtr* adjList; // This data type should be the same as info
};

#endif

