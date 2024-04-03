#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <ctime>

class Card {
public:
    int value;
    std::string name;

    Card(int v, std::string n) : value(v), name(n) {}
};

class Deck {
public:
    std::vector<Card> cards;

    Deck() {
        std::string names[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 4; j++) {
                cards.push_back(Card(i < 9 ? i + 2 : 10, names[i]));
            }
        }
        std::srand(unsigned(std::time(0)));
        std::random_shuffle(cards.begin(), cards.end());
    }

    Card drawCard() {
        Card card = cards.back();
        cards.pop_back();
        return card;
    }
};

int main() {
    Deck deck;
    int playerScore = 0;
    int dealerScore = 0;
    char choice;

    playerScore += deck.drawCard().value;
    dealerScore += deck.drawCard().value;

    while (true) {
        std::cout << "Your score: " << playerScore << std::endl;
        std::cout << "Dealer's score: " << dealerScore << std::endl;
        std::cout << "Do you want to draw another card? (y/n): ";
        std::cin >> choice;

        if (choice == 'y') {
            playerScore += deck.drawCard().value;
            if (playerScore > 21) {
                std::cout << "You busted! Dealer wins.\n";
                break;
            }
        }
        else {
            while (dealerScore < 17) {
                dealerScore += deck.drawCard().value;
            }
            if (dealerScore > 21) {
                std::cout << "Dealer busted! You win.\n";
            }
            else if (dealerScore > playerScore) {
                std::cout << "Dealer wins.\n";
            }
            else {
                std::cout << "You win.\n";
            }
            break;
        }
    }

    std::cout << "Final scores:\n";
    std::cout << "Player: " << playerScore << std::endl;
    std::cout << "Dealer: " << dealerScore << std::endl;

    std::ofstream file;
    file.open("game.txt");
    file << "Player's final score: " << playerScore << std::endl;
    file << "Dealer's final score: " << dealerScore << std::endl;
    file.close();

    return 0;
}