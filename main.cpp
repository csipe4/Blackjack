#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::cout << "\033[2J\033[1;1H";
#endif
}

struct Card {
    string rank;
    string suit;
    int value;
};

void deal(vector<Card>& hand, vector<Card>& deck, int& total) {
    Card card = deck.back();
    deck.pop_back();
    hand.push_back(card);
    total += card.value;
}

void printPlayerHand(vector<Card>& playerHand, int total) {
    cout << "Your hand: ";
    for (const Card& card : playerHand) {
        cout << "[" << card.rank << " of " << card.suit << "] ";
    }
    cout << "Total: " << total << endl;
}

void printDealerHand(vector<Card>& dealerHand, int total) {
    cout << "Dealer's hand: ";
    for (const Card& card : dealerHand) {
        cout << "[" << card.rank << " of " << card.suit << "] ";
    }
    cout << "Total: " << total << endl;
}

int main() {
    bool playAgain = true;
   while (playAgain == true) {
    vector<string> suits = {"Hearts", "Diamonds", "Clubs", "Spades"};
    vector<string> ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    vector<Card> deck;
    vector<Card> playerHand;
    vector<Card> dealerHand;
    int playerTotal = 0;
    int dealerTotal = 0;

    for(string suit : suits){
        for(string rank : ranks) {
            int value;
            if (rank == "J" || rank == "Q" || rank == "K") {value = 10;}
            else if (rank == "A") {value = 11;}
            else {value = stoi(rank);}
            
            Card card{rank, suit, value};
            deck.push_back(card);
        }
    }

    shuffle(deck.begin(), deck.end(), mt19937(random_device{}()));

    deal(playerHand, deck, playerTotal);
    deal(dealerHand, deck, dealerTotal);
    deal(playerHand, deck, playerTotal);
    deal(dealerHand, deck, dealerTotal);

    

    string choice;
    bool turnOver = false;
    while (!turnOver && playerTotal < 21) {
        clearScreen();
        printPlayerHand(playerHand, playerTotal);
        cout << "Dealer's hand: " << "[" << dealerHand[0].rank << " of " << dealerHand[0].suit << "] [???] Total: ???" << endl;
        cout << "Do you want to [H]it or [S]tand?" << endl;
        cin >> choice;
        if (choice == "H" || choice == "h") {
            clearScreen();
            deal(playerHand, deck, playerTotal);
            printPlayerHand(playerHand, playerTotal);
            cout << "Dealer's hand: " << "[" << dealerHand[0].rank << " of " << dealerHand[0].suit << "] [???] Total: ???" << endl;
        }
        else if (choice == "S" || choice == "s") {
            clearScreen();
            turnOver = true;
        }
        else {cout << "Invalid choice. Please try again" << endl;}
    }

    if (playerTotal > 21) {
        clearScreen();
        cout << "You busted! Dealer wins!" << endl;
        printPlayerHand(playerHand, playerTotal);
        printDealerHand(dealerHand, dealerTotal);
    }
    else {
        while (dealerTotal < 17) {
            clearScreen();
            printPlayerHand(playerHand, playerTotal);
            printDealerHand(dealerHand, dealerTotal);
            deal(dealerHand, deck, dealerTotal);
        }
        if (dealerTotal > 21) {
            clearScreen();
            printPlayerHand(playerHand, playerTotal);
            printDealerHand(dealerHand, dealerTotal);
            cout << "Dealer busted! You win!" << endl;
        }
        else if (playerTotal == 21 && dealerTotal != 21) {
            clearScreen();
            printPlayerHand(playerHand, playerTotal);
            printDealerHand(dealerHand, dealerTotal);
            cout << "BLACKJACK!!! YOU WIN!!!" << endl;
        }
        else if(playerTotal > dealerTotal) {
            clearScreen();
            printPlayerHand(playerHand, playerTotal);
            printDealerHand(dealerHand, dealerTotal);
            cout << "You win!" << endl;    
        }
        else if(playerTotal < dealerTotal) {
            clearScreen();
            printPlayerHand(playerHand, playerTotal);
            printDealerHand(dealerHand, dealerTotal);
            cout << "Dealer wins!" << endl;    
        }
        else{
            clearScreen();
            printPlayerHand(playerHand, playerTotal);
            printDealerHand(dealerHand, dealerTotal);
            cout << "Push! You tie!" << endl;
        }
    }
    string replay;
    cout << "Would you like to play again? Y/N?" << endl;
    cin >> replay;
    if(replay != "Y" && replay != "y") {
        playAgain = false;    
    }
   }
   cout << "Thanks for playing!" << endl;
}
