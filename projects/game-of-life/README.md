# Conway's Game of Life

## Introduction

Conway's Game of Life is a classic cellular automaton devised by mathematician John Conway in 1970. It's a zero-player game, meaning its evolution is determined by its initial state, with no further input. Despite its simplicity, the Game of Life is known for its complex and fascinating patterns.

## Rules :triangular_flag_on_post:

The Game of Life is played on an infinite two-dimensional grid of cells, each of which can be in one of two states: alive or dead. The game evolves in discrete generations, where the state of a cell in the next generation is determined by its current state and the following rules:

1. Any live cell with fewer than two live neighbors dies, as if by loneliness.
2. Any live cell with more than three live neighbors dies, as if by overcrowding.
3. Any live cell with two or three live neighbors lives, unchanged, to the next generation.
4. Any dead cell with exactly three live neighbors becomes a live cell.

These simple rules give rise to a variety of patterns and behaviors, making the Game of Life a fascinating area of study.

## Build :gear:

To run the Game of Life code, you'll need a C++ compiler such as g++. You can compile the code using the following command:

First `cd` into the game-of-life directory.

```bash
cd /projects/game-of-life
```

Then compile the project.

```bash
g++ game_of_life.cpp -o build/game_of_life
```

Or using make command:

```bash
make compile
```

## Running the Code

After compiling the code, you can run the Game of Life simulation using the following command:

```bash
./build/game_of_life
```

Or using make command:

```bash
make run
```

This will start the simulation, and you can watch how the cells evolve from one generation to the next based on the rules of the game.

## Code Structure

The code for Conway's Game of Life is implemented in C++ and structured as follows:

- **Cell**: A class representing a single cell in the grid. It has methods to calculate its next state based on the rules of the game and update itself accordingly.

- **GameBoard**: A class that represents the game board, which is a 2D grid of cells. It has methods to initialize the board, calculate the next generation, and display the current state of the board.

### `Cell` Class
The `Cell` class represents an individual cell within the Game of Life grid. It encapsulates the state (alive or dead) of the cell and provides methods to calculate its next state based on the rules of the game.

**Attributes**

- `X` and `Y` Coordinates: Each cell has X and Y coordinates on the grid, indicating its position.

- `State`: The state attribute represents whether the cell is alive or dead.

- `nextState`: This attribute stores the calculated next state of the cell during each tick of the simulation.

**Methods**

- `calculateNextState(const std::vector<Cell>& neighbors)`: Calculates the next state of the cell based on the states of its neighboring cells, following the Game of Life rules.

- `updateState()`: Updates the current state of the cell with its calculated next state after each tick.

- `isAlive()`: Checks whether the cell is alive `true` or dead `false`.

- `getX()` and `getY()`: Retrieve the X and Y coordinates of the cell.

- `revive()`: Changes the state of a cell to alive.

### `gameBoard` Class

The `gameBoard` class represents the entire Game of Life board, which is essentially a 2D grid of cells. It manages the board's size, initializes the grid with cells, and handles the simulation's progression.

**Attributes**
- `boardSize`: Specifies the size of the Game of Life board, determining the number of cells both in width and height on the grid.

- `board`: A 2D vector that stores the cells representing the grid.

**Methods**
- `initialize(const std::vector<std::pair<int, int>>& aliveCells)`: Initializes the board, setting specific cells to be alive based on the provided coordinates.

- `display()`: Displays the current state of the board in the console, with alive cells represented as '*' and dead cells as '.'.

- `tick()`: Advances the simulation by calculating and updating the next state of each cell on the board.

- `getNeighbors(int x, int y)`: Retrieves the neighboring cells of a given cell, taking into account the boundary conditions.

- `setBoardSize()`: Allows users to specify the board size interactively.

- `setUseDefaultPatterns()`: Prompts users to choose whether to use default initial patterns or provide custom configurations.

#### User Interaction

Both the `Cell` and `gameBoard` classes play crucial roles in simulating the Game of Life. The Cell class handles the state and behavior of individual cells, while the gameBoard class manages the entire grid and simulation progression. Users can interact with these classes to customize the simulation and observe the fascinating dynamics of the Game of Life.

### `Config` Class

The `Config` class is responsible for managing the configuration options for the Game of Life. It provides a structured way to specify various settings for the simulation. Users can either choose default configurations or customize them according to their preferences when running the program.

#### Configuration Options

1. **Board Size:** Specifies the size of the Game of Life board. This determines the number of cells both in width and height on the grid.

2. **Shift Pattern to Center:** Allows users to choose whether the initial pattern should be shifted to the center of the board or not.

3. **Default Initial Pattern:** Offers a selection of predefined initial patterns, including "Start Pattern" and "R-Pentomino Pattern."

4. **Number of Initial Alive Cells:** If not using default patterns, users can specify the number of initially alive cells.

5. **Initial Pattern for Alive Cells:** Users can define a custom pattern by providing a vector of coordinates for initially alive cells.

#### User Interaction

Upon running the Game of Life program, the `Config` class will prompt users to configure these options, making it easy to tailor the simulation to their preferences.


Feel free to explore the code, experiment with different initial configurations, and observe the intriguing patterns that emerge in Conway's Game of Life!

Happy coding!
