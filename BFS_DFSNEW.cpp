#include <iostream>
#include <stack>
#include <queue>
using namespace std;

void dfs(int adj_mat[5][5], int n, int start) {
    int visited[5] = {0};
    stack<int> stk;
    stk.push(start);
    visited[start] = 1;

    cout << "DFS: ";
    while (!stk.empty()) {
        int i = stk.top();
        stk.pop();
        cout << i << " --> ";
        for (int j = n - 1; j >= 0; j--) {
            if (adj_mat[i][j] == 1 && visited[j] == 0) {
                stk.push(j);
                visited[j] = 1;
            }
        }
    }
    cout << "NULL" << endl;
}

void bfs(int adj_mat[5][5], int n, int start) {
    int visited[5] = {0};
    queue<int> q;
    q.push(start);
    visited[start] = 1;

    cout << "BFS: ";
    while (!q.empty()) {
        int i = q.front();
        q.pop();
        cout << i << " --> ";
        for (int j = 0; j < n; j++) {
            if (adj_mat[i][j] == 1 && visited[j] == 0) {
                q.push(j);
                visited[j] = 1;
            }
        }
    }
    cout << "NULL" << endl;
}

int main() {
    // Predefined graph (Undirected)
    // Example: 0--1, 0--2, 1--3, 2--4
    int n = 5;
    int adj_mat[5][5] = {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 0, 1},
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0}
    };

    dfs(adj_mat, n, 0);  // DFS starting from node 0
    bfs(adj_mat, n, 0);  // BFS starting from node 0

    return 0;
}


/*
🔷 Graph Representation (Adjacency Matrix)
We are using this hardcoded adjacency matrix for 5 nodes:

cpp
Copy
Edit
int adj_mat[5][5] = {
    {0, 1, 1, 0, 0},  // 0 connected to 1 and 2
    {1, 0, 0, 1, 0},  // 1 connected to 0 and 3
    {1, 0, 0, 0, 1},  // 2 connected to 0 and 4
    {0, 1, 0, 0, 0},  // 3 connected to 1
    {0, 0, 1, 0, 0}   // 4 connected to 2
};
🧭 Visual Graph (Undirected)
markdown
Copy
Edit
     0
    / \
   1   2
   |    \
   3     4
Node 0 connects to 1 and 2

Node 1 connects to 3

Node 2 connects to 4

🔍 DFS Traversal (Depth-First Search)
Starts from 0, uses stack (LIFO). Always goes as deep as possible first.

text
Copy
Edit
Stack content and steps:
- Start at 0 → push(0)
- Pop 0 → visit → push 2, push 1 (reverse order)
- Pop 1 → visit → push 3
- Pop 3 → visit (no unvisited neighbors)
- Pop 2 → visit → push 4
- Pop 4 → visit (done)

Final Output:
DFS: 0 --> 1 --> 3 --> 2 --> 4 --> NULL
🔍 BFS Traversal (Breadth-First Search)
Starts from 0, uses queue (FIFO). Always explores neighbors first.

text
Copy
Edit
Queue content and steps:
- Start at 0 → enqueue(0)
- Dequeue 0 → visit → enqueue 1, enqueue 2
- Dequeue 1 → visit → enqueue 3
- Dequeue 2 → visit → enqueue 4
- Dequeue 3 → visit
- Dequeue 4 → visit

Final Output:
BFS: 0 --> 1 --> 2 --> 3 --> 4 --> NULL
📊 Summary Table
Step	DFS (Stack)	BFS (Queue)
1	0	0
2	1	1
3	3	2
4	2	3
5	4	4



*/