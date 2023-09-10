#include <iostream>
#include <vector>

#include <thread>  // For sleep_for
#include <chrono>  // For milliseconds

#ifdef _WIN32
#include <windows.h>  // For Windows-specific console functions
#else
#include <cstdlib>  // For Unix-like systems (Linux and macOS)
#endif

using namespace std;

// Enumeration to represent cell states
enum State { ALIVE = true, DEAD = false };


class Cell {
    public:
        // Constructor with default values
        Cell(int x = 0, int y = 0, State state = DEAD) : x(x), y(y), state(state) {}

        // Getter methods
        int getX() const { return x; }
        int getY() const { return y; }

        // Check if the cell is alive
        bool isAlive() const {
            return (state == ALIVE) ? true : false;
        }

        // Calculate the next state of the cell based on its neighbors
        void calculateNextState(const std::vector<Cell>& neighbors) {
            // Rules of the Game of Life:
            // 1. Any live cell with fewer than two live neighbours dies, as if by loneliness.
            // 2. Any live cell with more than three live neighbours dies, as if by overcrowding.
            // 3. Any live cell with two or three live neighbours lives, unchanged, to the next generation.
            // 4. Any dead cell with exactly three live neighbours comes to life.

            int liveNeighbors = 0;

            for (const Cell& neighbor : neighbors) {
                if (neighbor.isAlive()) {
                    liveNeighbors++;
                }
            }
            
            nextState = state; // Rule 3
            if (liveNeighbors < 2 || liveNeighbors > 3) {
                    nextState = DEAD;  // Rule 1 and Rule 2
            }
            if (liveNeighbors == 3) {
                    nextState = ALIVE;   // Rule 4
            }
        }

        // Update the state of the cell with its next state
        void updateState() {
            state = nextState;
        }

        // Custom print function
        void print() const {
            std::cout << "Cell(" << x << ", " << y << ")";
            if (state) {
                std::cout << " is Alive." << std::endl;
            } else {
                std::cout << " is Dead." << std::endl;
            }
        }

        // Revive the cell to the ALIVE state
        void revive() {
            state = ALIVE;
        }

    private:
        int x;
        int y;
        bool state;
        bool nextState;
};


class gameBoard {
    public:
         // Constructor with default board size
        gameBoard(int boardSize = 10) : boardSize(boardSize) {
            // Initialize the 2D vector with default Cell values
            board.resize(boardSize, std::vector<Cell>(boardSize));
        }

        // Initialize the board with a list of initial alive cells
        void initialize(const std::vector<std::pair<int, int>>& aliveCells) {
            for (const auto& coords : aliveCells) {
                int x = coords.first;
                int y = coords.second;

                // Check if the coordinates are within the board bounds
                if (x >= 0 && x < boardSize && y >= 0 && y < boardSize) {
                    board[x][y].revive(); // Set the cell to ALIVE
                }
            }
        }

        // Display the current state of the board
        void display() const {
            // Clear the terminal screen (platform-specific)
            #ifdef _WIN32
            system("cls");
            #else
            system("clear");
            #endif

            for (int i = 0; i < boardSize; i++) {
                for (int j = 0; j < boardSize; j++) {
                    if (board[i][j].isAlive()) {
                        std::cout << " *";
                    } else {
                        std::cout << " .";
                    }
                }
                std::cout << std::endl;
            }
        }

        // Calculate the next generation of the board
        void tick() {
            // Loop over all cells and calculate the next state
            for (int i = 0; i < boardSize; i++) {
                for (int j = 0; j < boardSize; j++) {
                    std::vector<Cell> neighbors = getNeighbors(i, j);
                    board[i][j].calculateNextState(neighbors);
                }
            }

            // Update all cells with their next state
            for (int i = 0; i < boardSize; i++) {
                for (int j = 0; j < boardSize; j++) {
                    board[i][j].updateState();
                }
            }
        }

    private:
        int boardSize;
        std::vector<std::vector<Cell>> board;

        std::vector<Cell> getNeighbors(int x, int y) const {
            std::vector<Cell> neighbors;

            // Define relative coordinates for neighbors
            int dx[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
            int dy[] = { -1, -1, -1, 0, 0, 1, 1, 1 };

            for (int i = 0; i < 8; i++) {
                int newX = x + dx[i];
                int newY = y + dy[i];

                // Check if the new coordinates are out of bounds
                if (newX >= 0 && newX < boardSize && newY >= 0 && newY < boardSize) {
                    neighbors.push_back(board[newX][newY]);
                } else {
                    // Out of bounds, use a default cell
                    neighbors.push_back(Cell(newX, newY, DEAD));
                }
            }

            return neighbors;
        }
};

// Function to shift initialize pattern to the center
void shiftToCenter(vector<pair<int, int>>& points, int boardSize) {
    int shiftAmount = boardSize / 2 - 1;
    for (auto& point : points) {
        point.first += shiftAmount;
        point.second += shiftAmount;
    }
}

int main() {
    int boardSize = 30; // You can change the board size as needed
    gameBoard board(boardSize);

    // Define the initial ALIVE cells - Star Pattern
    // std::vector<std::pair<int, int>> initialAliveCells = {
    //     {5, 5}, {4, 5}, {6, 5}, {4, 4}, {4, 6}
    // };

    // R-Pentomino Pattern
    std::vector<std::pair<int, int>> initialAliveCells = {
        {0, 0}, {0, -1}, {0, 1}, {-1, 0}, {1, -1}
    };

    // Shift the initial alive cells to the center
    shiftToCenter(initialAliveCells, boardSize);

    // Initialize the board with the initial ALIVE cells
    board.initialize(initialAliveCells);

    while (true) {
        // Display the current state of the board
        board.display();

        // Sleep for 1 second
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Update the board by ticking
        board.tick();
    }

    return 0;
}