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

## Code Structure :laptop:

The code for Conway's Game of Life is implemented in C++ and structured as follows:

- **Cell**: A class representing a single cell in the grid. It has methods to calculate its next state based on the rules of the game and update itself accordingly.

- **GameBoard**: A class that represents the game board, which is a 2D grid of cells. It has methods to initialize the board, calculate the next generation, and display the current state of the board.

## Installation :gear:

To run the Game of Life code, you'll need a C++ compiler such as g++. You can compile the code using the following command:

```bash
g++ game_of_life.cpp -o game_of_life
```

## Running the Code

After compiling the code, you can run the Game of Life simulation using the following command:

```bash
./game_of_life
```


This will start the simulation, and you can watch how the cells evolve from one generation to the next based on the rules of the game.

Feel free to explore the code, experiment with different initial configurations, and observe the intriguing patterns that emerge in Conway's Game of Life!

Happy coding!
