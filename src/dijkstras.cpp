#include "dijkstras.h"

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

        for (const Edge& edge : G.adjacencyList[u]) {
            int v = edge.dst;
            int w = edge.weight;
            if (!G.visited[v] && G.distance[u] + w < G.distance[v]) {
                G.distance[v] = G.distance[u] + w;
                previous[v] = u;
                pq.push({v, G.distance[v]});
            }
        }
    }
    return G.distance;
}

vector<int> extract_shortest_path(const vector<int>& dist, const vector<int>& prev, int destination) {
    if (destination < 0 || destination >= (int)dist.size() || dist[destination] == INF) {
        return {};
    }
    vector<int> path;
    for (int at = destination; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& path, int total) {
    if (total == INF) {
        cout << "No path found!" << endl;
        return;
    }
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i + 1 < path.size()) cout << " ";
    }
    cout << endl << "Total cost is " << total << endl;
}
