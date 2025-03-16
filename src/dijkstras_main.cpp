#include "dijkstras.h"

int main() {
    Graph G;

    // Load the graph from the file
    try {
        file_to_graph("/Users/elijahtabachnik/Desktop/Github/School/ics-46-hw-9-Elijahtab/src/medium.txt", G);
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    // Run Dijkstra from vertex 0
    int source = 0;
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    // Print distances
    cout << "Shortest distances from vertex " << source << ":\n";
    for (int i = 0; i < G.numVertices; i++) {
        cout << "Vertex " << i << ": ";
        if (distances[i] == INF) cout << "No path";
        else cout << distances[i];
        cout << "\n";
    }

    // Print paths
    cout << "\nShortest paths from vertex " << source << ":\n";
    for (int i = 0; i < G.numVertices; i++) {
        vector<int> path = extract_shortest_path(distances, previous, i);
        print_path(path, distances[i]);
    }

    return 0;
}
