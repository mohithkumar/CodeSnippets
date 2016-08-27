/**
Breadth First Search for Graphs
Premise for the program:
- A graph consists of a number of nodes and edges.
- An edge is made up of 2 nodes.

This program provides the following:
- Ability to add an edge (pair of nodes) to the graph
- Remove an edge from the graph
- Determine whether the graph is connected or not
- Iterative Breadth First Search (BFS), using STL Queue, of the entire graph
- Iterative Breadth First Search (BFS), using STL Queue, between any 2 given nodes.
- Return the number of nodes in the graph

The program basically builds an AdjacenyList from the input nodes and uses this AdjList for iterating through the graph.
*/

// File:

#include <iostream>
#include <queue>

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
    void breadthFirstSearch(int start, int end);
    uint getNumberOfNodes() const { return currSize; }

   private:
    uint iterativeBreadthFirstSearch(int start, int end);

    uint maxSize; // Max Number of Nodes 
    uint currSize; // Curr Number of Nodes
    NodePtr* adjList; // This data type should be the same as info
};

Graph::Graph(uint size) : currSize(0)
{
    if (size < 2)
        maxSize = 2;
    else
        maxSize = size;

    adjList = new NodePtr[maxSize];

    for (uint i = 0; i < maxSize; ++i)
        adjList[i] = NULL;
}

Graph::~Graph()
{
    for (uint i = 0; i < maxSize; ++i)
    {
        NodePtr curr = adjList[i];
        while(curr != NULL)
        {
            NodePtr prev = curr;
            curr = curr->next;
            delete prev;
        }
    }
    delete [] adjList;
}

bool Graph::isGraphConnected()
{
    bool checkConn(false);
    bool forLoopFlag(true);
    int startNode = END;

    // Find start node   
    for (uint i = 0; (i < maxSize) && (forLoopFlag == true); ++i)
    {
        NodePtr curr = adjList[i];
        if (curr != NULL)
        {
            startNode = curr->info;
            forLoopFlag = false;
        }
    }

    uint numOfVisitedNodes = iterativeBreadthFirstSearch(startNode, END);
    if (numOfVisitedNodes == currSize)
        checkConn = true;

    return checkConn;
}

// Returns false if the given edge is already present 
bool Graph::addEdge(int x, int y)
{
    bool addResult(false);
    if (currSize > maxSize)
    {
        cout << "Maximum number of Nodes " << maxSize << " inserted" << endl;
        return addResult;
    }

    bool xNodeInserted = true;
    bool yNodeInserted = true;
    bool forLoopFlag = true;

    // For X 
    for (uint i = 0; ((i < maxSize) && (forLoopFlag == true)); )
    {
        NodePtr curr = adjList[i];
        if (curr == NULL)
        {
            curr = new Node(x);
            adjList[i] = curr;
            ++currSize;
        }
        else
            ++i;

        if (curr->info == x)
        {
            while( (curr->next != NULL) && (curr->info != y) )
                curr = curr->next;

            if(curr->info != y)
            {
                NodePtr yNode = new Node(y);
                curr->next = yNode;
            }
            else
                yNodeInserted = false;

            forLoopFlag = false;
        }
    }

    // For Y
    forLoopFlag = true;
    for (uint i = 0; ((i < maxSize) && (forLoopFlag == true)); )
    {
        NodePtr curr = adjList[i];
        if (curr == NULL)
        {
            curr = new Node(y);
            adjList[i] = curr;
            ++currSize;
        }
        else
            ++i;

        if (curr->info == y)
        {
            while( (curr->next != NULL) && (curr->info != x) )
                curr = curr->next;

             if(curr->info != x)
            {
                NodePtr xNode = new Node(x);
                curr->next = xNode;
            }
            else
                xNodeInserted = false;

            forLoopFlag = false;
        }
    }

    if (xNodeInserted && yNodeInserted)
    {
        addResult = true;
    }

    return addResult;
}

// Returns false if the given edge is cannot be found 
bool Graph::removeEdge(int x, int y)
{
    bool remResult(false);
    if (currSize == 0)
    {
        cout << "No nodes present in Graph" << endl;
        return remResult;
    }

    bool xNodeRemoved = false;
    bool yNodeRemoved = false;
    bool forLoopFlag = true;

    // For X 
    for (uint i = 0; ((i < maxSize) && (forLoopFlag == true)); ++i)
    {
        NodePtr first = adjList[i];
        if (first != NULL)
        {
            if (first->info == x)
            {
                NodePtr prev = first;
                NodePtr curr = first->next;
                while ((curr != NULL) && (yNodeRemoved == false))
                {
                    NodePtr temp = curr->next;
                    if (curr->info == y)
                    {
                        prev->next = curr->next;
                        delete curr;
                        yNodeRemoved = true;
                    }
                    else
                    {
                        prev = prev->next;
                        curr = temp;
                    }
                }

                if (first == prev)
                {
                    delete first;
                    --currSize;
                }
                forLoopFlag = false;
            }
        }
    }

    forLoopFlag = true;
    // For Y
    for (uint i = 0; ((i < maxSize) && (forLoopFlag == true)); ++i)
    {
        NodePtr first = adjList[i];
        if (first != NULL)
        {
            if (first->info == y)
            {
                NodePtr prev = first;
                NodePtr curr = first->next;
                while ((curr != NULL) && (yNodeRemoved == false))
                {
                    NodePtr temp = curr->next;
                    if (curr->info == x)
                    {
                        prev->next = curr->next;
                        delete curr;
                        yNodeRemoved = true;
                    }
                    else
                    {
                        prev = prev->next;
                        curr = temp;
                    }
                }

                if (first == prev)
                {
                    delete first;
                    --currSize;
                }
                forLoopFlag = false;
            }
        }
    }

    if (xNodeRemoved || yNodeRemoved)
    {
        remResult = true;
    }

    return remResult;
}

void Graph::breadthFirstSearch(int start, int end)
{
    cout << "Breadth first Search starting from vertex " << start << endl;
    uint numOfNodes = iterativeBreadthFirstSearch(start, end);
    cout << "Number of nodes visited is " << numOfNodes << endl;
}

uint Graph::iterativeBreadthFirstSearch(int start, int end)
{
    NodePtr startNode;
    Node endNode;
    bool startNodeFound(false);
    bool endNodeFound(false);
    uint numberOfVisitedNodes(0);

    // Find the start and end Nodes and mark all Nodes as non-visited
    for (uint i = 0; i < currSize; ++i)
    {
        NodePtr curr = adjList[i];
        if (curr != NULL)
        {
            if (curr->info == start)
            {
                startNode = curr;
                startNodeFound = true;
            }
            if (curr->info == end)
            {
                endNode = *curr;
                endNodeFound = true;
            }
            curr = curr->next;
            while (curr != NULL)
            {
                curr->visited = false;
                curr = curr->next;
            }
        }
    }

    // cout << "Info for Traversal : " << startNode->info << "; " << endNode->info << endl;
    if (!startNodeFound)
    {
        cout << "Start node " << start << " not found" << endl;
        return numberOfVisitedNodes;
    }

    queue<NodePtr> q;
    q.push(startNode);

    bool found(false);
    while (!q.empty() && (found == false))
    {
        NodePtr temp = q.top();
        q.pop();

        if (temp->info == endNode.info)
        {
            found = true;
            ++numberOfVisitedNodes;
            cout << temp->info << " ";
        }
        else if (temp->visited == false)
        {
            cout << temp->info << " ";
            ++numberOfVisitedNodes;

            // Set visited as True wherever temp.info is found
            for (uint i = 0; i < currSize; ++i)
            {
                NodePtr curr = adjList[i];
                if (curr != NULL)
                    curr = curr->next;
                while (curr != NULL)
                {
                    if (curr->info == temp->info)
                    {
                        curr->visited = true;
                    }
                    curr = curr->next;
                }
            }

            // Find adjacent Nodes of temp
            bool forLoopFlag = false;
            NodePtr curr;
            for (uint i = 0; ((i < currSize) && (forLoopFlag == false)); ++i)
            {
                curr = adjList[i];
                if (curr->info == temp->info)
                {
                    forLoopFlag = true;
                }
            }

            while (curr->next != NULL)
            {
                curr = curr->next;
                if (curr->visited == false)
                {
                    // cout << "Insert - " << curr->info << endl;
                    q.push(curr);
                }
            }
        }
    }
    cout << endl;

     return numberOfVisitedNodes;
}

 int main()
{
    Graph g(20);
    g.addEdge(1, 2); g.addEdge(1, 3); g.addEdge(1, 4);
    g.addEdge(2, 5); g.addEdge(2, 6); g.addEdge(2, 9);
    g.addEdge(4, 7); g.addEdge(4, 8); g.addEdge(4, 9);
    g.addEdge(10,11);
    // cout << "Number of nodes : " << g.getNumberOfNodes() << endl;
    g.depthFirstSearch(1, 9);

    // cout << "(Graph Connected ? 0 = False : 1 = True) ==> " << g.isGraphConnected() << endl;

    g.removeEdge(1, 2);
    return 0;
}

// Feedback and suggestions welcome.
// Posted 13th March 2013 by Mohith Suryanarayan

