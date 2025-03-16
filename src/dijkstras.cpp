#include "dijkstras.h"
vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    int n = G.numVertices;
    vector<int> distance(n, INF);
    previous.assign(n, -1);
    
    distance[source] = 0;
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});
    
    while (!pq.empty()) {
        auto [dist_u, u] = pq.top();
        pq.pop();
        
        if (dist_u > distance[u]) continue;

        const vector<Edge>& edges = static_cast<const vector<vector<Edge>>&>(G)[u];

        for (const auto& edge : edges) {
            int v = edge.dst;
            int w = edge.weight;
            
            if (distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
                previous[v] = u;
                pq.push({distance[v], v});
            }
        }
    }
    
    return distance;
}



vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination)
{
    if (distances[destination] == INF) {
        return {};
    }

    vector<int> path;
    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }
    
    reverse(path.begin(), path.end());
    
    return path;
}

void print_path(const vector<int>& path, int total)
{
    if (path.empty()) {
        cout << "No path found.\n";
        return;
    }

    cout << "Shortest path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i] << " ";

    }
    cout << "\nTotal cost: " << total << "\n";
}
