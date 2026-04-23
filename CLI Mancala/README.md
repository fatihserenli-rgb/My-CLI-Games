
# 🪨 CLI Mancala

**CLI Mancala** is a terminal-based implementation of the classic board game Mancala (Mangala), written in C. It is part of the **My-CLI-Games** collection.

In this game, you play against a smart computer AI. The objective is to collect the most stones in your large cup (Mancala) by strategically distributing stones from the smaller cups on your side of the board.

## 🎮 Gameplay and Rules

The game board consists of 2 rows of 6 small cups and 2 large cups (one for each player). Each small cup starts with 6 stones.

* **Your Side:** The bottom row (Cups 1 to 6, from right to left). Your large cup is on the left.
* **Computer's Side:** The top row. The computer's large cup is on the right.
* **Turn Mechanics:** On your turn, choose a cup (1-6) on your side. The stones in that cup are distributed counter-clockwise, one by one, into the subsequent cups, including your large cup (but skipping the opponent's large cup).
* **Extra Turn:** If the last stone of your distribution lands in your own large cup, you get to play again!
* **End of Turn:** If the last stone lands in an empty cup, your turn ends, and it's the computer's turn.
* **Winning:** The game ends when one player's side is completely empty. The player with the most stones in their large cup wins.

## 🤖 The AI Opponent

The computer doesn't just play randomly! It simulates future moves on a virtual board (`fake_board`) to evaluate the best possible outcome. It prioritizes:
1. Moves that yield the maximum number of stones in its large cup.
2. Moves that grant an extra turn.
3. If neither is optimal, it strategically picks the highest indexed available cup.

## ⌨️ Controls

When it's your turn, the game will prompt you to select a cup:
* Enter a number between **`1`** and **`6`** to choose a cup from your side.
* Invalid inputs (like letters or out-of-bound numbers) are handled safely without crashing the game.

## 🚀 How to Run

To compile and play this game, you need a C compiler (like GCC) installed on your system.

1.  Open your terminal or command prompt.
2.  Navigate to the directory containing the source code and compile it:
    ```bash
    gcc Mancala.c -o mancala
    ```
3.  Run the compiled game:
    * **Linux / macOS:**
        ```bash
        ./mancala
        ```
    * **Windows:**
        ```bash
        mancala.exe
        ```

## 🛠️ Built With
* C Programming Language
* Standard C Libraries (`stdio.h`)

---
*This game is a part of the [My-CLI-Games](https://github.com/YOUR_USERNAME/My-CLI-Games) repository.*
