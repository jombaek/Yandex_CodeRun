#include <iostream>
#include <vector>
#include <string>

bool canCapture(const std::vector<std::vector<char>>& board, int row, int col, char player)
{
    char opponent = (player == 'w') ? 'b' : 'w';
    int numRows = board.size();
    int numCols = board[0].size();

    if (col < numCols - 2 && row < numRows - 2 && board[row + 1][col + 1] == opponent && board[row + 2][col + 2] == '\0')
        return true;

    if (col < numCols - 2 && row >= 2 && board[row - 1][col + 1] == opponent && board[row - 2][col + 2] == '\0')
        return true;

    if (col >= 2 && row < numRows - 2 && board[row + 1][col - 1] == opponent && board[row + 2][col - 2] == '\0')
        return true;

    if (col >= 2 && row >= 2 && board[row - 1][col - 1] == opponent && board[row - 2][col - 2] == '\0')
        return true;

    return false;
}

int main()
{
    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<char>> board(N, std::vector<char>(M));

    int w;
    std::cin >> w;

    for (int i = 0; i < w; ++i)
    {
        int row, col;
        std::cin >> row >> col;
        board[row - 1][col - 1] = 'w';
    }

    int b;
    std::cin >> b;

    for (int i = 0; i < b; ++i)
    {
        int row, col;
        std::cin >> row >> col;
        board[row - 1][col - 1] = 'b';
    }

    std::string currentPlayer;
    std::cin >> currentPlayer;

    bool canCaptureOpponent = false;
    char playerColor = (currentPlayer == "white") ? 'w' : 'b';

    for (int row = 0; row < N; ++row)
    {
        for (int col = 0; col < M; ++col)
        {
            if (board[row][col] == playerColor && canCapture(board, row, col, playerColor))
            {
                canCaptureOpponent = true;
                break;
            }
        }

        if (canCaptureOpponent)
            break;
    }

    if (canCaptureOpponent)
        std::cout << "Yes" << "\n";
    else
        std::cout << "No" << "\n";

    return 0;
}