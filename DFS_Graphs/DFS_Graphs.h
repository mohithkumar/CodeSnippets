#ifndef DFS_GRAPHS_H
#define DFS_GRAPHS_H

#include <cstddef>

using namespace std;

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
    void depthFirstSearch(int start, int end);
    uint getNumberOfNodes() const { return currSize; }

  private:
    uint iterativeDepthFirstSearch(int start, int end);

    uint maxSize; // Max Number of Nodes
    uint currSize; // Curr Number of Nodes
    NodePtr* adjList; // This data type should be the same as info
};

#endif

