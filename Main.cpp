/*
Daniel Pulido-Alaniz
6/12/2025

This program implements a basic blackjack game in 
the terminal using OOD principals. It includes user 
input for the player to manage their hand, automated 
dealer behavior for the player to compete against, and 
an option to play multiple rounds. 
*/
#include <iostream>
#include <vector>

using namespace std;


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

//Added code to print dealer cards
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

int dealIntialCards() {
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

/*
NEW FEATURE: Dealer
- This function handles how the dealer will play. 
- The dealer will continue to hit until they have
  reached a total of at least 17. 
- This function also determines who wins the game. 
*/

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

  int playerTotal = dealIntialCards();
  //int dealerTotal = dealInitialDealerCards();

  playerTotal = playerTurn(playerTotal);
  dealerTurn(playerTotal); 
}

/*
NEW FEATURE: play again
- Previous main() code was moved to runGame() function above. 
- When game ends, the user is asked if they want to play again. 
  If they respond with "y", player and dealer hands are reset 
  and runGame is called again. 
- Game terminates when user responds with "n" to play again prompt.
*/

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
