#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

const int SIZE = 3;

struct Node {
    vector<vector<char>> board;
    int g, h;
    bool isMax; // true for AI (O)
    pair<int, int> move;

    Node(vector<vector<char>> b, int g, bool isMax, pair<int, int> mv)
        : board(b), g(g), isMax(isMax), move(mv) {
        h = evaluate(b);
    }

    int f() const {
        return g + h;//Total cost = how far we’ve come (g) + how close we are to winning (h).
    }

    bool operator<(const Node& other) const {
        return f() > other.f(); // min-heap
    }

    static int evaluate(const vector<vector<char>>& b) {
        // Check rows, cols, diagonals for win/loss
        for (int i = 0; i < SIZE; i++) {
            if (b[i][0] == b[i][1] && b[i][1] == b[i][2] && b[i][0] != ' ') {
                return (b[i][0] == 'X') ? 100 : -100;
            }
            if (b[0][i] == b[1][i] && b[1][i] == b[2][i] && b[0][i] != ' ') {
                return (b[0][i] == 'X') ? 100 : -100;
            }
        }
        if (b[0][0] == b[1][1] && b[1][1] == b[2][2] && b[0][0] != ' ') {
            return (b[0][0] == 'X') ? 100 : -100;
        }
        if (b[0][2] == b[1][1] && b[1][1] == b[2][0] && b[0][2] != ' ') {
            return (b[0][2] == 'X') ? 100 : -100;
        }
        return 0;
    }

    static bool isTerminal(const vector<vector<char>>& b) {
        return evaluate(b) != 0 || countEmpty(b) == 0;
    }

    static int countEmpty(const vector<vector<char>>& b) {
        int cnt = 0;
        for (auto& row : b)
            for (char c : row)
                if (c == ' ') cnt++;
        return cnt;
    }
};

pair<int, int> aStarTicTacToe(vector<vector<char>> board) {
    priority_queue<Node> pq;
    pq.push(Node(board, 0, true, {-1, -1}));

    pair<int, int> best = {-1, -1};
    int minF = numeric_limits<int>::max();

    while (!pq.empty()) {
        Node cur = pq.top(); pq.pop();

        if (Node::isTerminal(cur.board)) {
            int val = Node::evaluate(cur.board);
            if (val == -100 && cur.f() < minF) {
                best = cur.move;
                minF = cur.f();
            }
            continue;
        }

        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (cur.board[i][j] == ' ') {
                    vector<vector<char>> newBoard = cur.board;
                    newBoard[i][j] = cur.isMax ? 'O' : 'X';
                    pq.push(Node(newBoard, cur.g + 1, !cur.isMax, cur.isMax ? make_pair(i, j) : cur.move));
                }
            }
        }
    }

    return best;
}

void printBoard(const vector<vector<char>>& board) {
    cout << "\n";
    for (auto& row : board) {
        for (char c : row)
            cout << (c == ' ' ? '.' : c) << " ";
        cout << "\n";
    }
    cout << "\n";
}

int main() {
    vector<vector<char>> board(3, vector<char>(3, ' '));
    int turn = 0;

    while (true) {
        printBoard(board);
        if (Node::isTerminal(board)) break;

        if (turn % 2 == 0) {
            int x, y;
            cout << "Enter your move (row col): ";
            cin >> x >> y;
            if (board[x][y] != ' ') {
                cout << "Invalid move!\n";
                continue;
            }
            board[x][y] = 'X';
        } else {
            cout << "AI (O) is thinking...\n";
            pair<int, int> mv = aStarTicTacToe(board);
            if (mv.first != -1) board[mv.first][mv.second] = 'O';
        }
        turn++;
    }

    printBoard(board);
    int result = Node::evaluate(board);
    if (result == 100) cout << "You win!\n";
    else if (result == -100) cout << "AI wins!\n";
    else cout << "It's a draw!\n";

    return 0;
}
/*
   0   1   2
0 [' ', ' ', ' ']
1 [' ', ' ', ' ']
2 [' ', ' ', ' ']

Players
Human → 'X'
AI → 'O' (uses A* Search to determine the best move)

f() = g + h;   // A* formula

X wins → +100
O wins → -100
No winner → 0

Enter your move (row col): 0 0
AI (O) is thinking...
Enter your move (row col): 1 1
AI (O) is thinking...
Enter your move (row col): 0 1
AI (O) is thinking...
Enter your move (row col): 0 2

evaluate(board)
→ Check rows, columns, diagonals:
   [X X X] → Player wins (+100)
   [O O O] → AI wins (-100)

Start with current board → Push into PQ
Explore all possible next moves → Add to PQ
Pop best node (lowest f) → Continue until terminal state
Return best move


*/