#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

constexpr int INF = numeric_limits<int>::max();

struct Node {
    int vertex;
    int distance;
    bool operator>(const Node& other) const {
        return distance > other.distance; 
    }
};

struct Edge {
    int src, dst, weight;
    Edge(int s, int d, int w) : src(s), dst(d), weight(w) {}
};

struct Graph {
    int numVertices;
    vector<vector<Edge>> adjacencyList;
    vector<int> dist;
    vector<int> prev;
    vector<bool> visited;

    Graph(int n) : numVertices(n) {
        adjacencyList.resize(n);
        dist.resize(n, INF);
        prev.resize(n, -1);
        visited.resize(n, false);
    }

    void addEdge(int u, int v, int w, bool undirected = true) {
        adjacencyList[u].push_back(Edge(u, v, w));
        if (undirected) {
            adjacencyList[v].push_back(Edge(v, u, w));
        }
    }
};

vector<int> dijkstra_shortest_path(Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    G.dist.assign(n, INF);
    G.visited.assign(n, false);
    previous.assign(n, -1);

    priority_queue<Node, vector<Node>, greater<Node>> pq;

    G.dist[source] = 0;
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
            if (!G.visited[v] && G.dist[u] + w < G.dist[v]) {
                G.dist[v] = G.dist[u] + w;
                previous[v] = u;
                pq.push({v, G.dist[v]});
            }
        }
    }
    return G.dist;
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
        cout << path[i] << " ";
    }
    cout << "\nTotal cost is " << total << "\n";
}
