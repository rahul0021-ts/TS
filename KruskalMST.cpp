#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, weight;
};

// Compare edges by weightS
bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}

// Disjoint Set Union (DSU)
int findParent(int node, vector<int>& parent) {
    if (parent[node] == node)
        return node;
    return parent[node] = findParent(parent[node], parent); // Path compression
}

void unionSets(int u, int v, vector<int>& parent) {
    parent[findParent(v, parent)] = findParent(u, parent);
}

int main() {
    int V = 5; // Number of vertices
    vector<Edge> edges = {
        {0, 1, 10}, {0, 2, 6}, {0, 3, 5},
        {1, 3, 15}, {2, 3, 4}
    };

    // Sort edges by weight
    sort(edges.begin(), edges.end(), compare);

    // Initialize disjoint sets
    vector<int> parent(V);
    for (int i = 0; i < V; i++)
        parent[i] = i;

    vector<Edge> mst;
    int totalCost = 0;

    for (Edge e : edges) {
        if (findParent(e.u, parent) != findParent(e.v, parent)) {
            mst.push_back(e);
            totalCost += e.weight;
            unionSets(e.u, e.v, parent);
        }
    }

    // Output MST
    cout << "Edges in MST:\n";
    for (Edge e : mst)
        cout << e.u << " - " << e.v << " = " << e.weight << "\n";

    cout << "Total cost of MST: " << totalCost << endl;

    return 0;
}

/*
🔍 Step-by-step Explanation
✅ Key Concepts Used
Graph Representation: List of edges (u, v, and weight)

Sorting Edges: Based on their weights (ascending)

Disjoint Set Union (DSU): To check for cycles and merge components

Path Compression: Optimization to make DSU faster

 Code Breakdown
struct Edge
Defines an edge between two vertices u and v with a certain weight.

compare(Edge a, Edge b)
Helps sort() function to sort edges based on their weights.

findParent(node, parent)
Finds the representative (or root) of a set using path compression.

unionSets(u, v, parent)
Unites two disjoint sets containing u and v.

int V = 5; // Number of vertices
vector<Edge> edges = {
    {0, 1, 10}, {0, 2, 6}, {0, 3, 5},
    {1, 3, 15}, {2, 3, 4}
};
⚙️ Execution Steps (Kruskal's Algorithm)
Sort edges by weight:

Sorted: (2–3, 4), (0–3, 5), (0–2, 6), (0–1, 10), (1–3, 15)

Add smallest edge if it doesn’t create a cycle:

Add (2–3, 4)

Add (0–3, 5)

Add (0–1, 10)

Skip (0–2) and (1–3) as they form cycles

Edges in MST:
2 - 3 = 4
0 - 3 = 5
0 - 1 = 10
Total cost of MST: 19

      10
   0 ----- 1
   | \     |
  6|  \5   |15
   |   \   |
   2----3
     4

Edges Selected:
2 - 3 (4)
0 - 3 (5)
0 - 1 (10)

Total Cost: 4 + 5 + 10 = 19

      10
   0 ----- 1
    \
     \
      3
     /
    /
   2

*/
