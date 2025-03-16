#include "dijkstras.h"
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <climits>

using namespace std;
vector<int> dijkstra_shortest_path(Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    G.distance.assign(n, INF); 
    G.visited.assign(n, false); 
    previous.assign(n, -1);     

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    G.distance[source] = 0;
    pq.push({source, 0});

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        int u = current.vertex;

        if (G.visited[u]) continue;
        G.visited[u] = true;

        for (const Edge& edge : G.adjacencyList[u]) { // Now correctly using Edge
            int v = edge.dst;  // Get destination vertex
            int weight = edge.weight;

            if (!G.visited[v] && G.distance[u] + weight < G.distance[v]) {
                G.distance[v] = G.distance[u] + weight;
                previous[v] = u;
                pq.push({v, G.distance[v]});
            }
        }
    }

    return G.distance;
}



vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    for (int at = destination; at != -1; at = previous[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& path, int total) {
    if (path.empty()) {
        cout << "No path found!" << endl;
        return;
    }
    cout << "Shortest path: ";
    for (size_t i = 0; i < path.size(); i++) {
        if (i > 0) cout << " -> ";
        cout << path[i];
    }
    cout << " (Total Distance: " << total << ")" << endl;
}