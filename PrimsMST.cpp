#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

#define V 5

int minKey(vector<int>& key, vector<bool>& inMST) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (!inMST[v] && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

void primMST(int graph[V][V]) {
    vector<int> parent(V);
    vector<int> key(V, INT_MAX);
    vector<bool> inMST(V, false);

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, inMST);
        inMST[u] = true;

        for (int v = 0; v < V; v++)
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    cout << "Edge \tWeight\n";
    for (int i = 1; i < V; i++)
        cout << parent[i] << " - " << i << " \t" << graph[i][parent[i]] << "\n";
}

int main() {
    int graph[V][V] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0},
    };

    primMST(graph);
    return 0;
}
/*
      2       3
  0 ----- 1 ----- 2
   \     |  \     |
    \    |   \    |
     6   8    5   7
      \  |     \  |
         3 ----- 4
             9

int graph[V][V] = {
    {0, 2, 0, 6, 0},
    {2, 0, 3, 8, 5},
    {0, 3, 0, 0, 7},
    {6, 8, 0, 0, 9},
    {0, 5, 7, 9, 0},
};

Edge    Weight
0 - 1     2
1 - 2     3
0 - 3     6
1 - 4     5

0 --2-- 1 --3-- 2
 |      |
 6      5
 |      |
 3      4







🔄 Step-by-Step Execution
Key Data Structures
key[]: min edge weight to connect a vertex

parent[]: stores MST (parent of each node)

inMST[]: boolean array to mark visited vertices

📌 Visual Trace of Prim’s Algorithm
Initial Setup:
r
Copy
Edit
Start from vertex 0
key[]    = [0, ∞, ∞, ∞, ∞]
parent[] = [-1, -, -, -, -]
inMST[]  = [F, F, F, F, F]
Iteration 1:
Pick min key: vertex 0 → Include in MST
Update neighbors (1 and 3)

r
Copy
Edit
key[]    = [0, 2, ∞, 6, ∞]
parent[] = [-1, 0, -, 0, -]
inMST[]  = [T, F, F, F, F]
Iteration 2:
Pick min key: vertex 1
Update neighbors (2, 4)

r
Copy
Edit
key[]    = [0, 2, 3, 6, 5]
parent[] = [-1, 0, 1, 0, 1]
inMST[]  = [T, T, F, F, F]
Iteration 3:
Pick min key: vertex 2
(only neighbor 4 has higher weight, no update)

r
Copy
Edit
key[]    = [0, 2, 3, 6, 5]
parent[] = [-1, 0, 1, 0, 1]
inMST[]  = [T, T, T, F, F]
Iteration 4:
Pick min key: vertex 4
Update neighbor 3 (weight 9 > current 6 → no change)

r
Copy
Edit
key[]    = [0, 2, 3, 6, 5]
parent[] = [-1, 0, 1, 0, 1]
inMST[]  = [T, T, T, F, T]
Iteration 5:
Pick min key: vertex 3 → All vertices now in MST.
*/