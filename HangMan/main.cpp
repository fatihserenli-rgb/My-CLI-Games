#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>

using namespace std;


void toLowerCase(string &str) {
    for (int i = 0; i < str.length(); i++) {
        str[i] = tolower(str[i]);
    }
}

int main() {
    string targetWord;

    cout << "--- ADAM ASMACA OYUNUNA HOS GELDINIZ ---\n\n";
    cout << "1. Oyuncu, lutfen gizli kelimeyi girin: ";
    cin >> targetWord;

    toLowerCase(targetWord);


    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"; //girilen kelimeyi gizlemeye çalıştım

    int attemptsLeft = 10;
    string hiddenWord(targetWord.length(), '_');
    string guess;

    cout << "--- OYUN BASLIYOR ---\n";
    cout << "2. Oyuncu, gizli kelimeyi bulmak icin 10 yanlis yapma hakkin var.\n";

    // Oyun Döngüsü
    while (attemptsLeft > 0 && hiddenWord != targetWord) {
        cout << "\n====================================\n";
        cout << "Gizli Kelime: ";
        for (int i = 0; i < hiddenWord.length(); i++) {
            cout << hiddenWord[i] << " ";
        }
        cout << "\nKalan Yanlis Hakkiniz: " << attemptsLeft << "\n";
        cout << "Bir harf VEYA tam kelime tahmin edin: ";
        cin >> guess;

        toLowerCase(guess);

        // 1. DURUM: Tek Harf Tahmini
        if (guess.length() == 1) {
            char letter = guess[0];
            bool found = false;

            for (int i = 0; i < targetWord.length(); i++) {
                if (targetWord[i] == letter) {
                    hiddenWord[i] = letter;
                    found = true;
                }
            }

            if (found) {
                cout << ">> Dogru! '" << letter << "' harfi kelimede var.\n";
            } else {
                cout << ">> Yanlis! '" << letter << "' harfi kelimede yok.\n";
                attemptsLeft--;
            }
        }
        // 2. DURUM: Tam Kelime Tahmini
        else {
            if (guess == targetWord) {
                hiddenWord = targetWord;
                cout << ">> Inanilmaz! Kelimeyi tek seferde bildin!\n";
            } else {
                cout << ">> Yanlis kelime tahmini!\n";
                attemptsLeft--; // Yanlış tahminde hakkı azalt
            }
        }
    }

    // Oyun Sonu Kontrolü
    cout << "\n====================================\n";
    if (hiddenWord == targetWord) {
        cout << "TEBRIKLER, KAZANDINIZ!\n";
        cout << "Gizli Kelime: " << targetWord << "\n";
    } else {
        cout << "KAYBETTINIZ! Adam asildi...\n";
        cout << "Gizli Kelime suydu: " << targetWord << "\n";
    }
    cout << "====================================\n";
    
    return 0;
}