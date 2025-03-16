#include "dijkstras.h"

Graph::Graph(int n) : numVertices(n) {
    adjacencyList.resize(n);
    distance.resize(n, INF);
    previous.resize(n, -1);
    visited.resize(n, false);
}

Graph::Graph() : numVertices(0) {}

void Graph::addEdge(int u, int v, int weight, bool isUndirected) {
    bool found = false;
    for (auto& e : adjacencyList[u]) {
        if (e.dst == v) {
            found = true;
            break;
        }
    }
    if (!found) {
        adjacencyList[u].push_back(Edge(u, v, weight));
    }
    if (isUndirected) {
        found = false;
        for (auto& e : adjacencyList[v]) {
            if (e.dst == u) {
                found = true;
                break;
            }
        }
        if (!found) {
            adjacencyList[v].push_back(Edge(v, u, weight));
        }
    }
}

istream& operator>>(istream& in, Graph& G) {
    if (!(in >> G.numVertices)) {
        throw runtime_error("Unable to read numVertices");
    }
    G.adjacencyList.resize(G.numVertices);
    G.distance.resize(G.numVertices, INF);
    G.previous.resize(G.numVertices, -1);
    G.visited.resize(G.numVertices, false);

    for (Edge e; in >> e;) {
        G.addEdge(e.src, e.dst, e.weight, true);
    }
    return in;
}

void file_to_graph(const string& filename, Graph& G) {
    ifstream file(filename);
    if (!file) {
        throw runtime_error("Can't open input file: " + filename);
    }
    file >> G;
    file.close();
}

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

        cout << path[i] << " ";
    }
    cout << "\nTotal cost is " << total << "\n";
}
