#include <iostream>
#include <vector>
#include <stdexcept>

class Xcircle
{
private:
    int boardSize;
    int winCondition;
    std::vector<std::vector<char>> board;
    char currentPlayer;

    void validateInput(int position) const
    {
        if (position < 1 || position > boardSize * boardSize)
        {
            throw std::invalid_argument("Invalid position. Please choose a number within the range.");
        }
        int row = (position - 1) / boardSize;
        int column = (position - 1) % boardSize;
        if (board[row][column] != ' ') 
        {
            throw std::invalid_argument("Position already taken. Choose another.");
        }
    }

    void switchPlayer()
    {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    bool checkWinCondition(int row, int column) const
    {
        // Check row
        int count = 0;
        for (int c = 0; c < boardSize; ++c) 
        {
            count = (board[row][c] == currentPlayer) ? count + 1 : 0;
            if (count == winCondition) return true;
        }

        // Check column
        count = 0;
        for (int r = 0; r < boardSize; ++r) 
        {
            count = (board[r][column] == currentPlayer) ? count + 1 : 0;
            if (count == winCondition) return true;
        }

        // Check main diagonal
        count = 0;
        for (int i = -winCondition; i <= winCondition; ++i)
        {
            int r = row + i, c = column + i;
            if (r >= 0 && r < boardSize && c >= 0 && c < boardSize)
            {
                count = (board[r][c] == currentPlayer) ? count + 1 : 0;
                if (count == winCondition) return true;
            }
        }

        // Check anti-diagonal
        count = 0;
        for (int i = -winCondition; i <= winCondition; ++i) 
        {
            int r = row + i, c = column - i;
            if (r >= 0 && r < boardSize && c >= 0 && c < boardSize) 
            {
                count = (board[r][c] == currentPlayer) ? count + 1 : 0;
                if (count == winCondition) return true;
            }
        }

        return false;
    }

    void displayBoard() const 
    {
        for (int i = 0; i < boardSize; ++i)
        {
            for (int j = 0; j < boardSize; ++j)
            {
                if (board[i][j] == ' ') 
                {
                    std::cout << (i * boardSize + j + 1);
                }
                else 
                {
                    std::cout << board[i][j];
                }
                if (j < boardSize - 1) std::cout << " | ";
            }
            std::cout << std::endl;
            if (i < boardSize - 1)
            {
                std::cout << std::string(boardSize * 4 - 3, '-') << std::endl;
            }
        }
    }

public:
    Xcircle(int n, int m) : boardSize(n), winCondition(m), currentPlayer('X')
    {
        if (n < m || n <= 0 || m <= 0)
        {
            throw std::invalid_argument("Invalid board or win condition size.");
        }
        board.resize(n, std::vector<char>(n, ' '));
    }

    void playGame() 
    {
        int turns = 0;
        while (turns < boardSize * boardSize) 
        {
            displayBoard();
            std::cout << "Player " << currentPlayer << ", enter your move (1-" << boardSize * boardSize << "): ";
            int position;
            try 
            {
                std::cin >> position;
                validateInput(position);
            }
            catch (const std::invalid_argument& e) 
            {
                std::cerr << e.what() << std::endl;
                continue;
            }

            int row = (position - 1) / boardSize;
            int column = (position - 1) % boardSize;
            board[row][column] = currentPlayer;
            ++turns;

            if (checkWinCondition(row, column)) 
            {
                displayBoard();
                std::cout << "Player " << currentPlayer << " wins!" << std::endl;
                return;
            }

            switchPlayer();
        }
        displayBoard();
        std::cout << "It's a draw!" << std::endl;
    }
};

int main() 
{
    try 
    {
        Xcircle game(4, 4);
        game.playGame();
        return 0;
    }
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
