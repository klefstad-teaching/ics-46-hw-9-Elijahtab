#include <iostream>
#include "dijkstras.h"

using namespace std;

int main() {
    int numVertices = 6;
    Graph graph(numVertices);

    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 2);
    graph.addEdge(1, 2, 5);
    graph.addEdge(1, 3, 10);
    graph.addEdge(2, 3, 3);
    graph.addEdge(3, 4, 7);
    graph.addEdge(4, 5, 1);
    graph.addEdge(3, 5, 8);

    int source = 0;

    vector<int> previous(graph.numVertices, -1);  

    vector<int> distances = dijkstra_shortest_path(graph, source, previous);

    cout << "Shortest distances from vertex " << source << ":\n";
    for (int i = 0; i < numVertices; i++) {
        if (distances[i] == INF)
            cout << "Vertex " << i << ": No path\n";
        else
            cout << "Vertex " << i << ": " << distances[i] << "\n";
    }

    cout << "\nShortest paths from vertex " << source << ":\n";
    for (int i = 0; i < numVertices; i++) {
        vector<int> path = extract_shortest_path(distances, previous, i);
        print_path(path, distances[i]);
    }

    return 0;
}
