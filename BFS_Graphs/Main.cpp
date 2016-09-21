#include "BFS_Graphs.h"

int main()
{
    Graph g(20);
    g.addEdge(1, 2); g.addEdge(1, 3); g.addEdge(1, 4);
    g.addEdge(2, 5); g.addEdge(2, 6); g.addEdge(2, 9);
    g.addEdge(4, 7); g.addEdge(4, 8); g.addEdge(4, 9);
    g.addEdge(10,11);
    // cout << "Number of nodes : " << g.getNumberOfNodes() << endl;
    g.breadthFirstSearch(1, 9);

    // cout << "(Graph Connected ? 0 = False : 1 = True) ==> " << g.isGraphConnected() << endl;

    g.removeEdge(1, 2);
    return 0;
}

