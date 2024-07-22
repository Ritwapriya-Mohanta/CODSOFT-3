#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class TicTacToe {
private:
    vector<vector<char>> board;
    char currentPlayer;
    int scoreX;
    int scoreO;

    void displayBoard() {
        cout << "\nCurrent Board:\n";
        cout << "     0   1   2\n";  // Column indices
        for (int i = 0; i < 3; ++i) {
            cout << "   +---+---+---+\n";  // Top border of each row
            cout << " " << i << " ";  // Row indices
            for (int j = 0; j < 3; ++j) {
                cout << "| " << board[i][j] << " ";
            }
            cout << "|\n";  // Right border of each row
        }
        cout << "   +---+---+---+\n";  // Bottom border of the last row
        cout << '\n';
    }

    bool isValidMove(int row, int col) {
        return row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == '.';
    }

    void updateBoard(int row, int col) {
        board[row][col] = currentPlayer;
    }

    bool checkWin() {
        // Check rows and columns
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer)
                return true;
            if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer)
                return true;
        }
        // Check diagonals
        if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer)
            return true;
        if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)
            return true;
        return false;
    }

    bool checkDraw() {
        for (const auto& row : board) {
            for (const auto& cell : row) {
                if (cell == '.')
                    return false;
            }
        }
        return true;
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    void displayScore() {
        cout << "\nScore:\n";
        cout << "Player X: " << scoreX << "\n";
        cout << "Player O: " << scoreO << "\n\n";
    }

public:
    TicTacToe() : board(3, vector<char>(3, '.')), currentPlayer('X'), scoreX(0), scoreO(0) {}

    void play() {
        cout << "Welcome to Tic Tac Toe!\n";
        while (true) {
            displayBoard();
            int row, col;
            cout << "Player " << currentPlayer << ", enter your move (row and column): ";
            while (!(cin >> row >> col) || !isValidMove(row, col)) {
                cout << "Invalid move. Enter row and column again: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            updateBoard(row, col);

            if (checkWin()) {
                displayBoard();
                cout << "Player " << currentPlayer << " wins! Congratulations!\n";
                if (currentPlayer == 'X') {
                    scoreX++;
                } else {
                    scoreO++;
                }
                displayScore();
                break;
            }

            if (checkDraw()) {
                displayBoard();
                cout << "The game is a draw!\n";
                displayScore();
                break;
            }

            switchPlayer();
        }
    }

    void reset() {
        board = vector<vector<char>>(3, vector<char>(3, '.'));
        currentPlayer = 'X';
    }
};

int main() {
    TicTacToe game;
    char playAgain = 'y';
    while (playAgain == 'y') {
        game.play();
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
        if (playAgain == 'y') {
            game.reset();
        }
    }
    return 0;
}
