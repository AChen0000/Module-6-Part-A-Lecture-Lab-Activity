#include "graph.h"
#include <vector>

graphType::graphType(int size)
{
    if (size >= 0)
    {
        maxSize = size;
    }
    else
    {
        maxSize = 0;
    }
    if (maxSize > 0)
    {
        graph.resize(maxSize);
    }
}

bool graphType::isEmpty() const
{
    return graph.empty();
}

void graphType::clearGraph()
{
    for (int i = 0; i < graph.size(); i++)
    {
        graph[i].destroyList();
    }
    graph.clear();
    maxSize = 0;
}

void graphType::createGraph(std::string filename)
{
    std::ifstream fin(filename);
    int index = 0;
    int vertex = 0;
    int adjcentVertex = 0;
    if (!isEmpty())
    {
        clearGraph();
    }
    if (!fin.is_open())
    {
        throw std::runtime_error("Cannot open input file.");
    }
    int gSize = 0;
    fin >> gSize;
    if (gSize > maxSize)
    {
        maxSize = gSize;
        graph.resize(maxSize);
    }
    for (index = 0; index < gSize; index++)
    {
        fin >> vertex;
        fin >> adjcentVertex;
        while (adjcentVertex != -999)
        {
            graph[vertex].insert(adjcentVertex);
            fin >> adjcentVertex;
        }
    }
    fin.close();
}

std::string graphType::printGraph()
{
    std::ostringstream out;
    for (int i = 0; i < graph.size(); i++)
    {
        out << i << " ";
        graph[i].print(out);
        out << std::endl;
    }
    return out.str();
}

std::string graphType::breadthFirstTraversal()
{
    linkedQueue<int> queue;
    bool *visited = new bool[graph.size()];
    for (int i = 0; i < graph.size(); i++)
        visited[i] = false;
    
    std::string out;
    for (int i = 0; i < graph.size(); i++)
    {
        if (!visited[i])
        {
            queue.enqueue(i);
            visited[i] = true;
            out += " " + std::to_string(i) + " ";
            
            while (!queue.isEmptyQueue())
            {
                int u = queue.dequeue();
                for (auto it = graph[u].begin(); it != graph[u].end(); ++it)
                {
                    int w = *it;
                    if (!visited[w])
                    {
                        queue.enqueue(w);
                        visited[w] = true;
                        out += " " + std::to_string(w) + " ";
                    }
                }
            }
        }
    }
    delete[] visited;
    return out;
}

std::string graphType::depthFirstTraversal()
{
    bool *visited = new bool[graph.size()];
    std::string output;
    for (int i = 0; i < graph.size(); i++)
        visited[i] = false;
    
    for (int i = 0; i < graph.size(); i++)
    {
        if (!visited[i])
        {
            dft(i, visited, output);
        }
    }
    delete[] visited;
    return output;
}

void graphType::dft(int v, bool visited[], std::string &output)
{
    visited[v] = true;
    output += " " + std::to_string(v) + " ";
    for (auto it = graph[v].begin(); it != graph[v].end(); ++it)
    {
        int w = *it;
        if (!visited[w])
        {
            dft(w, visited, output);
        }
    }
}

std::string graphType::dftAtVertex(int vertex)
{
    bool *visited = new bool[graph.size()];
    std::string output;
    for (int i = 0; i < graph.size(); i++)
        visited[i] = false;
    
    dft(vertex, visited, output);
    delete[] visited;
    return output;
}
// Here is the new connect function 
bool graphType::connected(int start, int end) {
    if (start == end) return true;
    if (start < 0 || end < 0 || start >= graph.size() || end >= graph.size()) 
        return false;

    std::vector<bool> visited(graph.size(), false);
    linkedQueue<int> q;
    
    visited[start] = true;
    q.enqueue(start);

    while (!q.isEmptyQueue()) {
        int current = q.front();
        q.dequeue();

        for (auto it = graph[current].begin(); it != graph[current].end(); ++it) {
            int neighbor = *it;
            if (neighbor == end) return true;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.enqueue(neighbor);
            }
        }
    }

    return false;
}

graphType::graphType(const graphType &otherGraph)
{
    maxSize = 0;
    copyGraph(otherGraph);
}

graphType::~graphType()
{
    clearGraph();
}

const graphType &graphType::operator=(const graphType &otherGraph)
{
    if (this != &otherGraph)
    {
        copyGraph(otherGraph);
    }
    return *this;
}

void graphType::copyGraph(const graphType &otherGraph)
{
    if (!this->isEmpty())
    {
        this->clearGraph();
    }

    this->maxSize = otherGraph.maxSize;
    graph.resize(otherGraph.graph.size());
    for (int i = 0; i < this->graph.size(); i++)
    {
        this->graph[i] = otherGraph.graph[i];
    }
}
