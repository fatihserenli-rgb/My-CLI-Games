# 🎓 ECTS Maze

**ECTS Maze** is a terminal-based maze game written in C, featured in the **My-CLI-Games** collection. 

In this game, you play as a student (`P`) whose ultimate goal is to reach the graduation point (`X`). However, your path is blocked by "ECTS (European Credit Transfer System) barrier" walls (`#`). You must navigate the map, collect the required credits, break through the walls, and graduate!

## 🎮 Gameplay and Rules

The game is played on a 16x16 grid. The map features two nested wall layers (inner and outer), and you need to accumulate a specific ECTS score to pass through each layer.

* **`P` (Player):** Represents you. You start at the center of the map.
* **`X` (Exit):** Your final destination (graduation).
* **`#` (Walls):** There are two layers of walls blocking your way.
* **`1` (Type 1 Credits):** Located inside the inner wall. Each is worth 8 ECTS. You must collect **32 ECTS** (4 items) to pass through the inner wall.
* **`2` (Type 2 Credits):** Located between the inner and outer walls. Each is worth 8 ECTS. You must collect **24 ECTS** (3 items) to pass through the outer wall.

If you attempt to walk through a wall without the required credits, the game will warn you: *"YOU DON'T HAVE ENOUGH ECTS FOR PASS THROUGH THIS WALL!"*

## ⌨️ Controls

You can move your character using the classic WASD keys (case-insensitive):

* **W:** Up
* **S:** Down
* **A:** Left
* **D:** Right

Type your move and press `Enter` to advance.

## 🚀 How to Run

To compile and play this game on your local machine, you need a C compiler (such as GCC) installed.

1.  Open your terminal or command prompt.
2.  Navigate to the directory containing the source code and compile it using the following command:
    ```bash
    gcc FatihMehmet_Serenli.c -o ects_maze
    ```
3.  Run the compiled game:
    * **Linux / macOS:**
        ```bash
        ./ects_maze
        ```
    * **Windows:**
        ```bash
        ects_maze.exe
        ```

## 🛠️ Built With
* C Programming Language
* Standard C Libraries (`stdio.h`, `stdlib.h`, `time.h`)

---
*This game is a part of the [My-CLI-Games](https://github.com/YOUR_USERNAME/My-CLI-Games) repository.*
