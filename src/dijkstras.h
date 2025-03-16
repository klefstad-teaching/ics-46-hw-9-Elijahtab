#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
#include <list>

using namespace std;

constexpr int INF = numeric_limits<int>::max();

struct Node {
    int vertex;
    int weight;
    bool operator>(const Node& other) const {
        return weight > other.weight;  // Min-heap (smallest weight first)
    }
};

struct Edge {
    int src=0;
    int dst=0;
    int weight=0;
    Edge(int s = 0, int d = 0, int w = 0) : src(s), dst(d), weight(w) {}
    friend istream& operator>>(istream& in, Edge& e)
    {
        return in >> e.src >> e.dst >> e.weight;
    }

    friend ostream& operator<<(ostream& out, const Edge& e)
    {
        return out << "(" << e.src << "," << e.dst << "," << e.weight << ")";
    }
};
struct Graph {
    int numVertices;
    vector<list<Node>> adjacencyList;
    vector<int> distance;
    vector<int> previous;
    vector<bool> visited;

    Graph(int n) : numVertices(n) {
        adjacencyList.resize(n);
        distance.resize(n, INF);
        previous.resize(n, -1);
        visited.resize(n, false);
    }

    void addEdge(int u, int v, int weight, bool isUndirected = true) {
        adjacencyList[u].push_back({v, weight});
        if (isUndirected) {
            adjacencyList[v].push_back({u, weight});
        }
    }
};


inline istream& operator>>(istream& in, Graph& G) {
    if (!(in >> G.numVertices))
        throw runtime_error("Unable to find input file");

    G.adjacencyList.resize(G.numVertices);
    for (Edge e; in >> e;) {
        G.addEdge(e.src, e.dst, e.weight, true);
    }
    return in;
}


inline void file_to_graph(const string& filename, Graph& G) {
    ifstream in(filename);
    if (!in) {
        throw runtime_error("Can't open input file");
    }
    in >> G;
    in.close();
}

vector<int> dijkstra_shortest_path(Graph& G, int source, vector<int>& previous);
vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination);
void print_path(const vector<int>& v, int total);
