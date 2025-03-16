#ifndef DIJKSTRAS_H
#define DIJKSTRAS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
#include <list>
#include <stdexcept>
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
    int src = 0;
    int dst = 0;
    int weight = 0;
    Edge(int s = 0, int d = 0, int w = 0) : src(s), dst(d), weight(w) {}
    friend istream& operator>>(istream& in, Edge& e) {
        return in >> e.src >> e.dst >> e.weight;
    }
    friend ostream& operator<<(ostream& out, const Edge& e) {
        return out << "(" << e.src << "," << e.dst << "," << e.weight << ")";
    }
};
struct Graph {
    int numVertices;
    vector<vector<Edge>> adjacencyList;
    vector<int> distance;
    vector<int> previous;
    vector<bool> visited;

    Graph(int n) : numVertices(n) {
        adjacencyList.resize(n);
        distance.resize(n, INF);
        previous.resize(n, -1);
        visited.resize(n, false);
    }
    Graph() : numVertices(0) {}

    void addEdge(int u, int v, int weight, bool isUndirected = true) {
        for (auto it = adjacencyList[u].begin(); it != adjacencyList[u].end(); ++it) {
            if (it->dst == v) {
                adjacencyList[u].erase(it);
                break;
            }
        }
        adjacencyList[u].push_back(Edge(u, v, weight));

        if (isUndirected) {
            for (auto it = adjacencyList[v].begin(); it != adjacencyList[v].end(); ++it) {
                if (it->dst == u) {
                    adjacencyList[v].erase(it);
                    break;
                }
            }
            adjacencyList[v].push_back(Edge(v, u, weight));
        }
    }

    auto begin() { return adjacencyList.begin(); }
    auto end()   { return adjacencyList.end(); }
};


inline istream& operator>>(istream& in, Graph& G) {
    if (!(in >> G.numVertices)) {
        throw runtime_error("Unable to read the number of vertices.");
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

inline void file_to_graph(const string& filename, Graph& G) {
    ifstream file(filename);
    if (!file) {
        throw runtime_error("Can't open input file: " + filename);
    }
    file >> G;
    file.close();
}

vector<int> dijkstra_shortest_path(Graph& G, int source, vector<int>& previous);
vector<int> extract_shortest_path(const vector<int>& dist, const vector<int>& prev, int destination);

void print_path(const vector<int>& path, int total);

#endif
