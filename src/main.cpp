#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

int main() {
    vector<string> suits = {"Hearts", "Diamonds", "Clubs", "Spades"};
    vector<string> ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    vector<string> deck;

    for(string suit : suits){
        for(string rank : ranks) {
            deck.push_back(rank + " of " + suit);
        }
    }
cout << "Hello world" << endl;
return 0;
}
