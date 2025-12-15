// file: tic_tac_toe.cpp
#include <algorithm>
#include <array>
#include <iostream>
#include <limits>

using namespace std;

int main() {
    int playerTurn = 1;
    array<array<int, 3>, 3> board{};
    char symbols[] = { ' ', 'X', 'O' };

    while (true) {
        // Print board
        cout << "\n";
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                cout << symbols[board[r][c]];
                if (c < 2) cout << " | ";
            }
            cout << "\n";
            if (r < 2) cout << "---+---+---\n";
        }

        cout << "\nPlayer " << playerTurn
            << "'s turn. Enter row and column (0-2): ";

        int row, col;
        if (!(cin >> row >> col)) {
            // handle non-integer input
            cout << "Invalid input. Please enter two integers (0-2).\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != 0) {
            cout << "Invalid move. Try again.\n";
            continue;
        }

        board[row][col] = playerTurn;

        // Check win
        bool win = false;
        for (int i = 0; i < 3; ++i) {
            if ((board[i][0] == playerTurn &&
                board[i][1] == playerTurn &&
                board[i][2] == playerTurn) ||
                (board[0][i] == playerTurn &&
                    board[1][i] == playerTurn &&
                    board[2][i] == playerTurn)) {
                win = true;
                break;
            }
        }

        if (!win &&
            ((board[0][0] == playerTurn &&
                board[1][1] == playerTurn &&
                board[2][2] == playerTurn) ||
                (board[0][2] == playerTurn &&
                    board[1][1] == playerTurn &&
                    board[2][0] == playerTurn))) {
            win = true;
        }

        if (win) {
            cout << "\nPlayer " << playerTurn << " wins!\n";
            break;
        }

        // Check draw
        bool draw = all_of(board.begin(), board.end(),
            [](const array<int, 3>& row) {
                return all_of(row.begin(), row.end(),
                    [](int cell) { return cell != 0; });
            });

        if (draw) {
            cout << "\nIt's a draw!\n";
            break;
        }

        playerTurn = (playerTurn == 1) ? 2 : 1;
    }

    return 0;
}
