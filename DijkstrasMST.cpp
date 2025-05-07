#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

#define V 5

int minDistance(vector<int>& dist, vector<bool>& visited) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (!visited[v] && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

void dijkstra(int graph[V][V], int src) {
    vector<int> dist(V, INT_MAX);
    vector<bool> visited(V, false);

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited);
        visited[u] = true;

        for (int v = 0; v < V; v++)
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    cout << "Vertex \tDistance from Source\n";
    for (int i = 0; i < V; i++)
        cout << i << " \t" << dist[i] << "\n";
}

int main() {
    int graph[V][V] = {
        {0, 10, 0, 0, 5},
        {0, 0, 1, 0, 2},
        {0, 0, 0, 4, 0},
        {7, 0, 6, 0, 0},
        {0, 3, 9, 2, 0},
    };

    dijkstra(graph, 0);
    return 0;
}

/*
🔍 Step-by-Step Explanation
✅ Key Concepts Used
Graph: Represented using a 2D adjacency matrix graph[V][V]

Dijkstra’s Algorithm: Greedy algorithm for shortest paths

Distance Array: Stores current shortest distances from the source

Visited Array: Tracks whether a vertex’s shortest distance is finalized

🧱 Code Breakdown
minDistance(vector<int>& dist, vector<bool>& visited)
Finds the unvisited vertex with the smallest distance value.

dijkstra(int graph[V][V], int src)
Initializes distances and visited status

Repeats for V - 1 vertices:

Picks the closest unvisited vertex u

Updates distances to its neighbors v if a shorter path is found through u

main()
Defines a 5x5 graph using an adjacency matrix

Calls dijkstra() with source vertex 0

int graph[V][V] = {
    {0, 10, 0, 0, 5},
    {0, 0, 1, 0, 2},
    {0, 0, 0, 4, 0},
    {7, 0, 6, 0, 0},
    {0, 3, 9, 2, 0},
};

     (10)       (1)
0 --------> 1 -------> 2
 \          ^          |
  \         |          v
  (5)     (3)        (4)
    \--> 4 -------> 3
          \         ^
           \-------/
             (2)

Dijkstra Execution from Source = 0
Initial distances: [0, ∞, ∞, ∞, ∞]

After processing:

Shortest path to 0 → 0

Shortest path to 1 → 8 (0 → 4 → 1)

Shortest path to 2 → 9 (0 → 4 → 1 → 2)

Shortest path to 3 → 7 (0 → 4 → 3)

Shortest path to 4 → 5 (0 → 4)

Vertex  Distance from Source
0       0
1       8
2       9
3       7
4       5

*/