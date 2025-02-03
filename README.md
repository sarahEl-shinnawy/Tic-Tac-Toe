# Tic Tac Toe - Raylib

A simple Tic Tac Toe game built using the Raylib library. This game features a graphical interface with a menu, player turn mechanics, and win/draw detection.

## Features
- **Graphical Interface**: Uses Raylib to display a clean and interactive Tic Tac Toe board.
- **Turn-Based Gameplay**: Players take turns placing their marks (X or O).
- **Win/Draw Detection**: The game detects when a player wins or if the game ends in a draw.
- **Main Menu**: A start menu allows players to begin the game.

## Controls
- **Left Mouse Click**: Place X or O on an empty cell.
- **Mouse Hover**: Highlight the "Play" button on the main menu.

## How to Run
1. **Install Raylib** (if not already installed):
   - Windows: Download and install from [Raylib Official Site](https://www.raylib.com/)
   - Linux/macOS: Install via package manager (e.g., `brew install raylib` on macOS)
   
2. **Compile the Game**:
   ```sh
   gcc tic_tac_toe.c -o tic_tac_toe -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
