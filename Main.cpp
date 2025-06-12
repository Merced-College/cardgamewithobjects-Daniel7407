#include <iostream>

using namespace std;

//your job is to fix this object
class Card { // Keeps a card object
public:
  //put the constructors and getters and setters here

private:
  //put data variables here, look below to see what data variables you should have
};

//define your getters and setters here

//the rest of the code is working code - if you define your object above
const string SUITS[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
const string RANKS[] = {"2", "3",  "4",    "5",     "6",    "7",  "8",
                        "9", "10", "Jack", "Queen", "King", "Ace"};
const int VALUES[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

// int DECK[52];
Card deck[52];
int currentCardIndex = 0;
/*
defines the arrays and variables related to a deck of playing cards through the
suits, ranks, the current card index, and the deck itself.
*/

void initializeDeck() {
  int deckIndex = 0;
  for (int suitIndex = 0; suitIndex < 4; suitIndex++) {
    for (int rankIndex = 0; rankIndex < 13; rankIndex++) {
      // Card(string suit, string rank, int value);
      deck[deckIndex++] =
          Card(SUITS[suitIndex], RANKS[rankIndex], VALUES[rankIndex]);
    }
  }
}

void printDeck() {
  for (int i = 0; i < 52; i++)
    deck[i].print_card();
}

void shuffleDeck() {
  srand((time(0)));
  for (int i = 0; i < 52; i++) {
    int index = rand() % 52;
    Card temp = deck[i]; // these next three lines are a swap function
    deck[i] = deck[index];
    deck[index] = temp;
  }
}

Card dealCard() { 
  return deck[currentCardIndex++]; 
}

int dealInitialPlayerCards() {
  Card card1 = dealCard();
  Card card2 = dealCard();
  cout << "Your cards: ";
  card1.print_card();
  card2.print_card();
  //cout << "Your cards: " << RANKS[card1 % 13] << " of " << SUITS[card1 / 13]
     //<< " and " << RANKS[card2 % 13] << " of " << SUITS[card2 / 13] << endl;
  return card1.get_value() + card2.get_value();
  //return cardValue(card1) + cardValue(card2);
}

int playerTurn(int playerTotal) {
  while (true) {
    cout << "Your total is " << playerTotal << ". Do you want to hit or stand?"
         << endl;
    string action;
    getline(cin, action);
    if (action == "hit") {
      Card newCard = dealCard();
      //playerTotal += cardValue(newCard);
      playerTotal += newCard.get_value();
      cout << "You drew a ";
      newCard.print_card();
      //cout << "You drew a " << RANKS[newCard % 13] << " of "
           //<< SUITS[newCard / 13] << endl;
      if (playerTotal > 21) {
        break;
      }
    } else if (action == "stand") {
      break;
    } else {
      cout << "Invalid action. Please type 'hit' or 'stand'." << endl;
    }
  }
  return playerTotal;
}


int main() {
  initializeDeck();
  //printDeck();
  shuffleDeck();
 //printDeck();

  int playerTotal = dealInitialPlayerCards();
  cout << "The playerTotal is " << playerTotal << endl;
  //int dealerTotal = dealInitialDealerCards();

  playerTotal = playerTurn(playerTotal);
  if (playerTotal > 21) {
    cout << "You busted! Dealer wins." << endl;
    return 0;
  } 
  
}
