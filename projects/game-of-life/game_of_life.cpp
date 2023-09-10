#include <iostream>
#include <vector>
#include <csignal> // For signal handling

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

class Config {
    public:
        int boardSize;
        
        bool useDefaultPatterns;
        
        enum DefaultInitialPattern { 
            START_PATTERN,
            RPENTOMINO_PATTERN
        } defaultInitialPattern;

        int numInitialAliveCells;
        
        std::vector<std::pair<int, int>> initialAliveCells;
      
        bool shiftToCenter;

        Config() {
            // Default configurations
            boardSize = 20;

            useDefaultPatterns = true;
            
            defaultInitialPattern = START_PATTERN;

            numInitialAliveCells = 0;  // Default is using default patterns

            shiftToCenter = true;            
        }

        void initializeConfig() {
            // Print a brief explanation of the Game of Life
            cout << "Welcome to the Game of Life!" << endl;
            cout << "The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970." << endl;
            cout << "It is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input." << endl;
            cout << "One interacts with the Game of Life by creating an initial configuration and observing how it evolves." << endl;
            cout << "The rules of the game are simple but can result in complex patterns." << endl;
            cout << "Each cell on the board can be either alive ('*') or dead ('.')." << endl;
            cout << "The next generation of cells is determined by the following rules:" << endl;
            cout << "1. Any live cell with fewer than two live neighbours dies, as if by loneliness." << endl;
            cout << "2. Any live cell with more than three live neighbours dies, as if by overcrowding." << endl;
            cout << "3. Any live cell with two or three live neighbours lives, unchanged, to the next generation." << endl;
            cout << "4. Any dead cell with exactly three live neighbours comes to life." << endl;
            cout << "Let's configure your Game of Life!" << endl;

            // Get user input for configuration
            setBoardSize();

            setUseDefaultPatterns();
            
            if (useDefaultPatterns) {
                setDefaultInitialPattern();
            }
            else {
                setCustomInitialPattern();
            }
            
            setShiftToCenter();

            // Print the current configuration
            printConfig();
        }

        // Set board size from user input
        void setBoardSize() {
            cout << "Enter board size (default is 20): ";
            string input;
            getline(cin, input);
            if (!input.empty()) {
                boardSize = stoi(input);
            }
        }

        // Set whether to shift the pattern to the center
        void setUseDefaultPatterns() {
            string choice;
            cout << "Choose from default initial patterns? (Y/N, default is Y): ";
            getline(cin, choice);
            useDefaultPatterns = (choice == "Y" || choice == "y" || choice.empty());
        }

        // Set the initial pattern from user input
        void setDefaultInitialPattern() {
            string input;
            int choice;
            cout << 
                "Choose an initial pattern (0: Start Pattern, 1: R-Pentomino Pattern) (default is Star Pattern): ";
            getline(cin, input);
            if (input.empty()) {
                choice = 0; // Set to default star pattern if Enter is pressed
            } else {
                choice = stoi(input);
            }

            defaultInitialPattern = static_cast<DefaultInitialPattern>(choice);

            // TODO: use case switch
            if (defaultInitialPattern == Config::START_PATTERN) {
                initialAliveCells = {
                    {0, 0}, {-1, 0}, {1, 0}, {-1, -1}, {-1, 1}
                };
            } else if (defaultInitialPattern == Config::RPENTOMINO_PATTERN) {
                initialAliveCells = {
                    {0, 0}, {0, -1}, {0, 1}, {-1, 0}, {1, -1}
                };
            }
        }


        // Set the custom number of initial alive cells and the pattern from user input
        void setCustomInitialPattern() {
            cout << "Enter the number of custom initial alive cells: ";
            cin >> numInitialAliveCells;
            if (numInitialAliveCells > 0) {
                initialAliveCells.reserve(numInitialAliveCells);
                cout << "Enter " << numInitialAliveCells << " initial alive cell coordinates (x y):" << endl;
                for (int i = 0; i < numInitialAliveCells; i++) {
                    int x, y;
                    cin >> x >> y;
                    initialAliveCells.push_back({x, y});
                }
            }
        }

        // Set whether to shift the pattern to the center
        void setShiftToCenter() {
            string choice;
            cout << "Shift the pattern to the center (Y/N, default is Y): ";
            getline(cin, choice);
            shiftToCenter = (choice == "Y" || choice == "y" || choice.empty());

            if (shiftToCenter) {
                int shiftAmount = boardSize / 2 - 1;
                for (auto& point : initialAliveCells) {
                    point.first += shiftAmount;
                    point.second += shiftAmount;
                }
            }
        }

        // Print the current configuration
        void printConfig() {
            cout << "Current Configuration:" << endl;
            cout << "Board Size: " << boardSize << endl;
            if (useDefaultPatterns) {
                cout << "Default Initial Pattern: " << (defaultInitialPattern == START_PATTERN ? "Start Pattern" : "R-Pentomino") << endl;
            }
            else {
                cout << "Number of Custom Initial Alive Cells: " << numInitialAliveCells << endl;                
            }

            cout << "Initial Alive Cells: ";
            for (const auto& cell : initialAliveCells) {
                cout << "(" << cell.first << ", " << cell.second << ") " << endl;
            }
            
            cout << "Shift to Center: " << (shiftToCenter ? "Yes" : "No") << endl;
            cout << endl;
            for (int i=3; i > 0; i--) {
                cout << "Starting the Game of Life in " << i << " seconds... " << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }        
};

// Function to handle the SIGINT signal (Ctrl + C)
void handleInterruptSignal(int signal) {
    cout << "\nGracefully shutting down the Game of Life..." << endl;
    exit(0);
}

int main() {

    // Set up a signal handler for SIGINT (Ctrl + C)
    signal(SIGINT, handleInterruptSignal);

    Config config;

    config.initializeConfig();

    gameBoard board(config.boardSize);

    // Initialize the board with the initial ALIVE cells
    board.initialize(config.initialAliveCells);

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