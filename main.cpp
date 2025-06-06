#include "graph.h"
#include <iostream>
#include <fstream>

// lecture activity for part A add the function connected to the graph class.
// connected returns true if two vertexes are connected
// it will return false if they are not.

int main()
{
    graphType g;
    g.createGraph("graph.txt");
    std::cout << g.printGraph() << std::endl;
    std::ofstream fout("g.txt");
    fout << g.printGraph();

    std::cout << g.depthFirstTraversal() << std::endl
              << std::endl
              << std::endl;
    std::cout << g.breadthFirstTraversal() << std::endl;
    graphType h(g);
    std::cout << h.printGraph() << std::endl;

    return 0;
}
