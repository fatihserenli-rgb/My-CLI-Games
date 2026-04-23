# 💣 CLI Minesweeper

**CLI Minesweeper** is a terminal-based adaptation of the classic puzzle game, written in C++ using Object-Oriented Programming (OOP) principles.

## 🎮 Gameplay and Rules

* **The Grid:** The game is played on a 10x10 board with 10 hidden mines.
* **Coordinates:** Rows are labeled with letters (`A` to `J`), and columns are labeled with numbers (`0` to `9`).
* **Objective:** This is a classic minesweeper game. Reveal all safe cells. You win when the only unrevealed cells left are the ones containing mines.
* **Clues:** When you open a safe cell, it will display a number indicating how many mines are hidden in its 8 neighboring cells. If a cell has no adjacent mines, it will automatically open all surrounding safe cells!
* **Flags:** If you suspect a cell hides a mine, you can place a Flag (`F`) on it to prevent yourself from accidentally opening it.

## ⌨️ How to Play (Controls)

The game requires you to input your moves using a specific coordinate format: 
**`[Action] [Row] [Column]`**

* **Actions:** * `A` -> Reveal (Open) a cell.
  * `B` -> Place/Remove a Flag.
* **Example Moves:**
  * `A C 5` (Press Enter): Opens the cell at Row C, Column 5.
  * `B A 0` (Press Enter): Places a flag on the cell at Row A, Column 0.

*(Note: The input is case-insensitive. `a c 5` works exactly the same as `A C 5`.)*

## ✨ Key Technical Features

This project was built to practice several advanced programming concepts:
* **Recursive Flood-Fill Algorithm:** When a player opens an empty cell (0 adjacent mines), the game uses recursion to automatically fan out and reveal all connected empty cells, exactly like the original game.
* **Robust Input Validation:** The game features strict `std::cin` error handling. It gracefully catches invalid data types, out-of-bounds coordinates, and random keystrokes without crashing or entering infinite loops.
* **Object-Oriented Design:** The board is built using a 2D `std::vector` of `Cell` structs, encapsulating properties like `isMine`, `isRevealed`, and `isFlagged` for clean and scalable code.

## 🚀 How to Run

To compile and play this game, you need a C++ compiler (like G++) installed on your system.

1.  Open your terminal or command prompt.
2.  Navigate to the directory containing the source code and compile it:
    ```bash
    g++ minesweeper.cpp -o minesweeper
    ```
3.  Run the compiled game:
    * **Linux / macOS:**
        ```bash
        ./minesweeper
        ```
    * **Windows:**
        ```bash
        minesweeper.exe
        ```
