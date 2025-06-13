#include <iostream>
#include <vector>

using namespace std;

//your job is to fix this object
class Card { // Keeps a card object
public:
  Card() : Card("Hearts", "2", 2){}

  Card (string suit, string rank, int value){
    this->suit = suit; 
    this->rank = rank; 
    this->value = value; 
  }

  string getSuit(){
    return suit; 
  }

  string getRank(){
    return rank; 
  }

  int getValue(){
    return value; 
  }

  void setSuit(string suit){
    this->suit = suit; 
  }

  void setRank(string rank){
    this->rank = rank; 
  }

  void setValue(int value){
    this->value = value; 
  }

  void print_card(){
    cout << rank << " of " << suit << endl; 
  }

private:
  string suit; 
  string rank; 
  int value; 
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
vector<Card> playerHand = {}; 
vector<Card> dealerHand = {};
bool isPlayerDone; 
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

void printGameCards(int playerTotal, int dealerTotal){
  cout << "\033[2J\033[1;1H";
  cout << "Your cards: " << endl;
  for(int i = 0; i < playerHand.size(); i++){
    playerHand[i].print_card(); 
  }

  if(isPlayerDone){
    cout << "Your total is " << playerTotal << ". \n";
  }

  cout << "\nDealer's cards:" << endl; 
  if(isPlayerDone){
    for(int i = 0; i < dealerHand.size(); i++){
      dealerHand[i].print_card(); 
    }
  } else {
    dealerHand[0].print_card(); 
    cout << "Flipped over card" << endl; 
  }

  if(isPlayerDone){
    cout << "Dealer total is " << dealerTotal << ". \n";
  }
  cout << endl; 
}

int dealInitialPlayerCards() {
  isPlayerDone = false; 
  Card card1 = dealCard();
  playerHand.push_back(card1); 
  Card card2 = dealCard();
  playerHand.push_back(card2); 

  Card dealerCard1 = dealCard(); 
  dealerHand.push_back(dealerCard1);
  Card dealerCard2 = dealCard(); 
  dealerHand.push_back(dealerCard2);

  int playerTotal = card1.getValue() + card2.getValue();

  printGameCards(playerTotal, card1.getValue()); 
  //cout << "Your cards: " << RANKS[card1 % 13] << " of " << SUITS[card1 / 13]
     //<< " and " << RANKS[card2 % 13] << " of " << SUITS[card2 / 13] << endl;
  return playerTotal;
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
      playerHand.push_back(newCard); 
      //playerTotal += cardValue(newCard);
      playerTotal += newCard.getValue();
      printGameCards(playerTotal, dealerHand[0].getValue()); 
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

int dealerTurn(int playerTotal){
  isPlayerDone = true; 
  int dealerTotal = dealerHand[0].getValue() + dealerHand[1].getValue(); 
  printGameCards(playerTotal, dealerTotal); 
  if (playerTotal > 21){
    cout << "You busted! Dealer wins." << endl; 
    return 0; 
  }

  while (dealerTotal < 17){
    Card newCard = dealCard(); 
    dealerHand.push_back(newCard); 
    dealerTotal += newCard.getValue(); 
    printGameCards(playerTotal, dealerTotal); 
  }

  if (dealerTotal > 21){
    cout << "Dealer busted! You win." << endl; 
  }  else if (dealerTotal < playerTotal){
    cout << "You are closer to 21! You win." << endl; 
  } else if (dealerTotal > playerTotal){
    cout << "Dealer is closer to 21! Dealer wins." << endl; 
  } else {
    cout << "Tie! No one wins." << endl; 
  }

  return 0; 
}

void runGame(){
  initializeDeck();
  //printDeck();
  shuffleDeck();
 //printDeck();

  int playerTotal = dealInitialPlayerCards();
  //int dealerTotal = dealInitialDealerCards();

  playerTotal = playerTurn(playerTotal);
  dealerTurn(playerTotal); 
}


int main() {
  string keepPlaying = "y"; 
  while (keepPlaying == "y"){
    dealerHand.clear(); 
    playerHand.clear(); 
    runGame(); 
    cout << "Do you want to play again? (y/n): ";
    while (true){
      getline(cin, keepPlaying);
      if (keepPlaying == "y"){
        break; 
      } else if (keepPlaying == "n"){
        break; 
      } else {
        cout << "Invalid option. Try again" << endl;
        cout << "Do you want to play again? (y/n): " << endl;
      }
    }
  }

  cout << "Thanks for playing!" << endl; 
}
