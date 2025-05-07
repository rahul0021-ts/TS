#include <iostream>
#include <vector>
using namespace std;

int N;
vector<vector<int>> board;
vector<bool> col, diag1, diag2;

void printBoard() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << (board[i][j] ? "Q " : ". ");
        cout << endl;
    }
    cout << "--------------------\n";
}

bool solve(int row) {
    if (row == N) {
        printBoard(); // One valid solution found
        return true;  // return true to stop at first solution
    }

    for (int c = 0; c < N; c++) {
        if (!col[c] && !diag1[row - c + N - 1] && !diag2[row + c]) {
            board[row][c] = 1;
            col[c] = diag1[row - c + N - 1] = diag2[row + c] = true;

            if (solve(row + 1)) // Recursive step
                return true;    // Stop at first solution

            // Backtrack
            board[row][c] = 0;
            col[c] = diag1[row - c + N - 1] = diag2[row + c] = false;
        }
    }

    return false;
}

int main() {
    cout << "Enter the value of N (number of queens): ";
    cin >> N;

    board = vector<vector<int>>(N, vector<int>(N, 0));
    col = vector<bool>(N, false);
    diag1 = vector<bool>(2 * N - 1, false); // "/" diagonals
    diag2 = vector<bool>(2 * N - 1, false); // "\" diagonals

    if (!solve(0))
        cout << "No solution exists for N = " << N << endl;

    return 0;
}
/*
How It Works
A queen can attack in:

the same column (col[c])

the same main diagonal \ (diag2[row + col])

the same anti-diagonal / (diag1[row - col + N - 1])

The algorithm recursively places queens row-by-row, checking for safety, and backtracks when stuck.

🧠 Key Variables
Variable	Description
board	2D grid to store queen positions (0 or 1)
col	Tracks used columns
diag1	Tracks / diagonals (row - col + N - 1)
diag2	Tracks \ diagonals (row + col)

📥 Sample Input
mathematica
Copy
Edit
Enter the value of N (number of queens): 4
📤 Output (One Valid Solution)
css
Copy
Edit
. Q . . 
. . . Q 
Q . . . 
. . Q . 
--------------------
📝 Q denotes a queen. . denotes an empty space.

🔄 Recursive Flow (Backtracking)
Try placing a queen in row 0 at every column

For each valid position, recursively go to the next row

If no valid position in a row, backtrack and change previous queen

If you reach row == N, you found a valid configuration

🎯 Visual Representation
For N = 4, one valid configuration:

java
Copy
Edit
Row 0:     . Q . .       → Queen at (0,1)
Row 1:     . . . Q       → Queen at (1,3)
Row 2:     Q . . .       → Queen at (2,0)
Row 3:     . . Q .       → Queen at (3,2)
Each queen is:

In a unique row (guaranteed by recursive depth)

In a unique column (col[])

On a unique / diagonal (diag1[])

On a unique \ diagonal (diag2[])

✅ Summary
Feature	Description
Approach	Backtracking
Solution Type	First valid configuration
Time Complex.	O(N!) worst-case
Space Complex.	O(N²) for board + O(N) for tracking


*/