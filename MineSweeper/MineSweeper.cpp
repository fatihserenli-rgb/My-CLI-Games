#include <iostream>
#include <vector>
#include <cstdlib> // srand, rand, system
#include <ctime>   // time
#include <cctype>  // toupper

using namespace std;



struct Cell {
    bool isMine = false;
    bool isRevealed = false;
    bool isFlagged = false;
    int neighborMines = 0;
};

class Minesweeper {
private:
    int rows;
    int cols;
    int totalMines;
    int cellsRevealed;
    bool gameOver;
    bool gameWon;
    vector<vector<Cell>> board;
    string message;

    // Mayınları rastgele yerleştirir
    void placeMines() {
        int placedMines = 0;
        while (placedMines < totalMines) {
            int r = rand() % rows;
            int c = rand() % cols;
            if (!board[r][c].isMine) {
                board[r][c].isMine = true;
                placedMines++;
            }
        }
    }

    // Her hücre için etrafındaki mayın sayısını hesaplar
    void calculateNeighbors() {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (board[r][c].isMine) continue;

                int count = 0;
                // Komşu 8 hücreyi kontrol et
                for (int dr = -1; dr <= 1; dr++) {
                    for (int dc = -1; dc <= 1; dc++) {
                        int nr = r + dr;
                        int nc = c + dc;
                        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && board[nr][nc].isMine) {
                            count++;
                        }
                    }
                }
                board[r][c].neighborMines = count;
            }
        }
    }

    void revealEmptyCells(int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols || board[r][c].isRevealed || board[r][c].isFlagged) {
            return;
        }

        board[r][c].isRevealed = true;
        cellsRevealed++;

        // Eğer etrafında mayın varsa, sadece o sayıyı göster ve ilerlemeyi durdur
        if (board[r][c].neighborMines > 0) {
            return;
        }

        // Eğer etrafında mayın yoksa komsu hucreyi de aç
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (dr != 0 || dc != 0) {
                    revealEmptyCells(r + dr, c + dc);
                }
            }
        }
    }

public:
    Minesweeper(int r = 10, int c = 10, int mines = 10) {
        rows = r;
        cols = c;
        totalMines = mines;
        cellsRevealed = 0;
        gameOver = false;
        gameWon = false;
        message = "Oyuna baslamak icin bir hamle yapin.";

        board.resize(rows, vector<Cell>(cols));

        srand(time(0));

        placeMines();
        calculateNeighbors();
    }

    void printBoard() {
        cout << "--- MAYIN TARLASI ---\n\n";

        cout << "    ";
        for (int c = 0; c < cols; c++) {
            cout << c << " ";
        }
        cout << "\n   " << string(cols * 2 + 1, '-') << "\n";

        for (int r = 0; r < rows; r++) {
            cout << (char)('A' + r) << " | ";
            for (int c = 0; c < cols; c++) {
                if (board[r][c].isRevealed) {
                    if (board[r][c].isMine) {
                        cout << "* ";
                    } else if (board[r][c].neighborMines == 0) {
                        cout << "  ";
                    } else {
                        cout << board[r][c].neighborMines << " ";
                    }
                } else if (board[r][c].isFlagged) {
                    cout << "F ";
                } else {
                    cout << ". ";
                }
            }
            cout << "|\n";
        }
        cout << "   " << string(cols * 2 + 1, '-') << "\n\n";

        if (!message.empty()) {
            cout << ">> " << message << "\n\n";
        }
    }

    void play() {
        while (!gameOver && !gameWon) {
            printBoard();

            char action, rowChar;
            int col;

            cout << "Hamle Formati -> [Islem] [Satir] [Sutun]\n";
            cout << "(Islem: Acmak icin 'A', Bayrak icin 'B')\n";
            cout << "Ornek: A C 5 (C satiri 5. sutunu acar)\n";
            cout << "Hamleniz: ";

            // 1. KONTROL: Veri Tipi ve Format Doğrulaması
            if (!(cin >> action >> rowChar >> col)) {
                cin.clear();
                cin.ignore(10000, '\n');
                message = "Hata: Gecersiz format! Lutfen ornekteki gibi aralarinda bosluk birakarak girin.";
                continue;
            }

            action = toupper(action);
            rowChar = toupper(rowChar);
            int row = rowChar - 'A';

            // 2. KONTROL: Sınır ve Mantık Doğrulaması
            if (row < 0 || row >= rows || col < 0 || col >= cols) {
                message = "Hata: Tahta sinirlari disinda bir koordinat girdiniz! (Satir: A-J, Sutun: 0-9)";
                continue;
            }
            if (action != 'A' && action != 'B') {
                message = "Hata: Gecersiz islem! Sadece 'A' (Ac) veya 'B' (Bayrak) kullanabilirsiniz.";
                continue;
            }

            // --- TÜM KONTROLLER GEÇİLDİ, HAMLEYİ İŞLE ---
            if (action == 'B') {
                if (board[row][col].isRevealed) {
                    message = "Hata: Acik bir hucreye bayrak koyamazsiniz.";
                } else {
                    board[row][col].isFlagged = !board[row][col].isFlagged;
                    message = "Bayrak durumu degistirildi.";
                }
            } else if (action == 'A') {
                if (board[row][col].isFlagged) {
                    message = "Uyari: Bayrakli hucreyi acamazsiniz. Once bayragi kaldirin.";
                } else if (board[row][col].isRevealed) {
                    message = "Uyari: Bu hucre zaten acik.";
                } else if (board[row][col].isMine) {
                    // MAYINA BASTIN!
                    gameOver = true;
                    // Butun mayinlari goster
                    for(int r = 0; r < rows; r++) {
                        for(int c = 0; c < cols; c++) {
                            if(board[r][c].isMine) board[r][c].isRevealed = true;
                        }
                    }
                    message = "BOOOM! Mayina bastiniz. Oyun bitti!";
                } else {
                    // Guvenli hucre, recursive acma islemini baslat
                    revealEmptyCells(row, col);
                    message = "Hucreler acildi.";
                }
            }

            // Kazanma durumu kontrolü
            if (!gameOver && cellsRevealed == (rows * cols - totalMines)) {
                gameWon = true;
                message = "TEBRIKLER! Butun guvenli alanlari actiniz ve kazandiniz!";
            }
        }

        printBoard(); // Oyun bittiğinde son durumu göstermek için
    }
};

int main() {
    // 10x10 boyutunda ve 10 mayınlı klasik başlangıç seviyesi
    Minesweeper game(10, 10, 10);
    game.play();
    return 0;
}
