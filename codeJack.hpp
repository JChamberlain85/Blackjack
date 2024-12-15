// Programmer: Josh Chamberlain
// Date: 4/5/2024
// File: codeJack.cpp  main.cpp
// Assignment: HW5
// Purpose: Gambling.

#ifndef CODEJACK_H
#define CODEJACK_H
#include <iostream>
#include <string>
#include <cstdlib>

struct card {
  int val;
  std::string suit;
  std::string face;
};


//Description: If Player Lucky: gives good advice, else: gives random advice
//Pre: none
//Post: Suggest User Action 
template <typename T>
std::string adviseOptimalActionOnLuck(const T probability, const int pVal, const int dCard1, const bool half, int& gChoice) {
  T threshold = rand() % 100 + 1;
  if (threshold <= probability) {
    if (pVal >= 9 && pVal <= 11 && half == 1) {
      gChoice = 3;
      return "Double Down";
    } else if (pVal <= 11) {
      gChoice = 1;
      return "Hit";
    } else if (pVal >= 17) {
      gChoice = 2;
      return "Stand";
    } else {
      if (dCard1 >= 7) {
        gChoice = 1;
        return "Hit";
      } else {
        gChoice = 2;
        return "Stand";
      }
    }
  } else {
    if (half == 1) {
      int decision = rand() % 3;
      switch (decision) {
        case 0:
          gChoice = 1;
          return "Hit";
        case 1:
          gChoice = 2;
          return "Stand";
        case 2: 
          gChoice = 3;
          return "Double Down";
        default:
          return "Error";
      }
    } else {
      gChoice = rand() % 2 + 1;
      return (gChoice == 1 ? "Hit" : "Stand");
    }
  }
}



//Description: Initiates Game
//Pre: Player Must have a Name
//Post: Gives Player Starting Balance
void gameStartUp(std::string& name, double& balance);

//Description: Draws Card
//Pre: None
//Post: Random int 2-14, numerical representation of card draw
int generateRandomCard();

//Description: Draws Card With Bias Towards 10 if lukcy
//Pre: User Luck
//Post: 10 if Lucky otherwise reverts to generateRandomCard()
int generateRandomCard(const int probability);

//Description: Assigns Face Card to 12-14 Cards
//Pre: Card Must be 12-14
//Post: Face Card Value
std::string faceCard(int& aceCounter, int& val);

//Description: Assigns Random Suit
//Pre: none
//Post: Returns Random Suit
std::string cardSuit();

//Description: Calculates Player Hand Value
//Pre: none
//Post: Player Hand Value
int pHandVal(int& aceCounter, bool& reset, int val1, int val2=0);

//Description: Calculates Dealer Hand Value
//Pre: None
//Post: Dealer Hand Value
int dHandVal(int& aceCounter, bool& reset, int val1, int val2=0);

//Description: Checks for Blackjack
//Pre: none
//Post: Returns True if Blackjack, False if not
bool isBlackjack(const int val);

//Description: Plays through Dealer's Turn
//Pre: Player hand Val less than 22
//Post: Returns Final Dealer Hand Value
int dealerTurn(int val1, int val2, bool& reset, int& aceCounter);

//Description: Updates Player Balance
//Pre: Wager made and Round Finished
//Post: Returns New Balance based on Wager and Bonus
float updatePlayerBalance(double& balance, float wager, float bonus, const bool doubleDown, const int pChoice, const int gChoice, bool win, bool bjWin);

//Description: Shows Game Stats
//Pre: End of Game
//Post: Returns All Relavent Stats from Game
void displayGameSummary(const int rounds, const int wins, const int bjWins, const int losses, const int bjLosses, const int ties, const int bjTies, const double startBalance, const double balance);

#endif
