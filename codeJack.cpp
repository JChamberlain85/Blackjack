#include "codeJack.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>

void gameStartUp(std::string& name, double& startBalance) {
  std::cout << "Welcome to Codejack! Please enter your name before you begin: ";
  getline(std::cin, name);
  startBalance = (rand() % (100000 - 10000 + 1) + 10000) / 100.00;
  return;
}

int generateRandomCard() {
  return rand() % 13 + 2;
}

int generateRandomCard(const int probability) {
  int luck = rand() % 100;
  if (luck < 15) {
    int chance = rand() % 100;
    if (chance < probability) {
      return 10;
    }
  }
  return generateRandomCard();
}

std::string faceCard(int& aceCounter, int& val) {
  switch (val) {
    case 11:
      aceCounter += 1;
      return "Ace";
    case 12:
      val = 10;
      return "Jack";
    case 13:
      val = 10;
      return "Queen";
    case 14: 
      val = 10;
      return "King";
    default:
      return "error";
  }
}

std::string cardSuit() {
  int k = rand() % 4;
  switch (k) {
    case 0:
      return "Hearts";
    case 1:
      return "Diamonds";
    case 2: 
      return "Clubs";
    case 3:
     return "Spades";
    default:
      return "error";
  }
}

int pHandVal(int& aceCounter, bool& reset, int val1, int val2) {
  static int score;
  if (reset == 1) {
    score = 0;
    reset = 0;
  }
  score = val1 + val2;
  while (aceCounter > 0 && score > 21) {
    score -= 10; // Changes ace value
    --aceCounter;
  }
  return score;
}

int dHandVal(int& aceCounter, bool& reset, int val1, int val2) {
  static int score;
  if (reset == 1) {
    score = 0;
    reset = 0;
  }
  score = val1 + val2;
  while (aceCounter > 0 && score > 21) {
    score -= 10; // Changes ace value
    --aceCounter;
  }
  return score;
}

bool isBlackjack(const int val) {
  return (val == 21);
}

int dealerTurn(int val1, int val2, bool& reset, int& aceCounter) {
  int dVal = val1 + val2;
  do {
    if (dVal < 17) {
      card newCard;
      newCard.val = generateRandomCard();
      newCard.suit = cardSuit();
      if (newCard.val > 10) {
        newCard.face = faceCard(aceCounter, newCard.val);
      }
      dVal = dHandVal(aceCounter, reset, dVal, newCard.val);
    } else if (dVal >= 17 && dVal <= 21){
      return dVal;
    }
  } while (dVal < 22);
  return 0;
}

float updatePlayerBalance(double& balance, float wager, float bonus, const bool doubleDown, const int pChoice, const int gChoice, bool win, bool bjWin) {
  bonus = 1;
  if (win) {
    bonus += (pChoice != gChoice) ? 0.80 : 0;
    bonus += bjWin ? 0.50 : 0;
    bonus += doubleDown ? 1 : 0;
    
    balance += wager * bonus;
  } else {
    bonus += (pChoice != gChoice) ? 0.20 : -0.20;
    bonus += doubleDown ? 1 : 0;
    
    balance -= wager * bonus;
  }
  return round(balance * 100) / 100;
}

void displayGameSummary(const int rounds, const int wins, const int bjWins, const int losses, const int bjLosses, const int ties, const int bjTies, const double startBalance, const double balance) {
  std::cout << "=== Game Summary ===" << std::endl;
  std::cout << "Total Rounds Played: " << rounds << std::endl;
  std::cout << "Total Wins (Regular): " << wins << std::endl;
  std::cout << "Total Wins (Blackjack): " << bjWins << std::endl;
  std::cout << "Total Losses (Regular): " << losses << std::endl;
  std::cout << "Total Losses (Blackjack): " << bjLosses << std::endl;
  std::cout << "Total Ties (Regular): " << ties << std::endl;
  std::cout << "Total Ties (Blackjack): " << bjTies << std::endl;
  std::cout << "Final Balance: $" << balance << std::endl;
  std::cout << "Net Gain/Loss: $" << balance - startBalance << std::endl;
}
