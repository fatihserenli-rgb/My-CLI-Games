# 🪢 CLI Hangman (Adam Asmaca)

**CLI Hangman** is a classic, terminal-based word-guessing game written in C++. It is part of the **My-CLI-Games** collection. 

This is a local 2-player game where one player acts as the "Host" who sets a secret word, and the other acts as the "Guesser" who tries to figure it out before running out of lives!

## 🎮 Gameplay and Rules

* **Player 1 (Host):** Starts the game by typing a secret word.
* **Player 2 (Guesser):** Must guess the hidden word. The word is represented by underscores (`_`). 
* **Attempts:** The Guesser has **10 incorrect attempts** (lives). 
* **Guessing Options:** On each turn, Player 2 can either:
  1.  **Guess a single letter:** If the letter exists in the word, it will be revealed in its correct positions. If not, 1 attempt is lost.
  2.  **Guess the entire word:** If the player thinks they know the word, they can type it completely. If it's correct, they win immediately. If wrong, 1 attempt is lost.
* **Case-Insensitive:** You don't need to worry about Caps Lock! "APPLE" and "apple" are treated exactly the same.

## 🚀 How to Run

To compile and play this game, you need a C++ compiler (like G++) installed on your system.

1.  Open your terminal or command prompt.
2.  Navigate to the directory containing the source code and compile it:
    ```bash
    g++ hangman.cpp -o hangman
    ```
3.  Run the compiled game:
    * **Linux / macOS:**
        ```bash
        ./hangman
        ```
    * **Windows:**
        ```bash
        hangman.exe
        ```

## 🛠️ Built With
* C++ Programming Language
* Standard C++ Libraries (`<iostream>`, `<string>`, `<cstdlib>`, `<cctype>`)

---
*This game is a part of the [My-CLI-Games](https://github.com/YOUR_USERNAME/My-CLI-Games) repository.*
