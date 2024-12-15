#include "codeJack.hpp"
#include <iostream>
#include <string>
#include <cstdlib>


int main() {
  srand(time(0));
  
  //Pre-game
  std::string name;
  double startBalance, balance;
  gameStartUp(name, startBalance);
  balance = startBalance;
  
  //Play
  bool replay = 1;
  char play;
  float wager, bonus = 0;
  int rounds = 1, wins = 0, losses = 0, ties = 0, bjWins = 0, bjLosses = 0, bjTies = 0, pVal = 0, dVal = 0, pAceCount = 0, dAceCount = 0, gChoice = 0;
  bool stand, doubleDown, first, dReset, pReset, half;
  std::string userInput, advice;
  
  do {
    do {
      std::cout << "Your balance is: $" << balance << "\nPlease enter wager amount: $";
      std::cin >> wager;
      if (wager > balance || wager < 0) {
        std::cout << "That is not a valid amount, keep in mind your balance is: $" << balance << std::endl;
      }
    } while (wager > balance);
    
    int probability = rand() % 100 + 1;
    int luck = rand() % 100 + 1;
    int pChoice = 0;
    bool pWin = 0;
    bool pBjWin = 0;
    bool pTie = 0;
    doubleDown = 0;
    first = 1;
    pAceCount = 0;
    dAceCount = 0;
    dReset = 1;
    pReset = 1;
    half = wager * 2 <= balance;
    
    //Draw Player's First Card
    card pCard1;
    pCard1.val = generateRandomCard(probability);
    pCard1.suit = cardSuit();
    if (pCard1.val > 10) {
      pCard1.face = faceCard(pAceCount, pCard1.val);
    }
    
    //Draw Player's Second Card
    card pCard2;
    pCard2.val = generateRandomCard(probability);
    pCard2.suit = cardSuit();
    if (pCard2.val > 10) {
      pCard2.face = faceCard(pAceCount, pCard2.val);
    }
    
    pVal = pHandVal(pAceCount, pReset, pCard1.val, pCard2.val);
    
    //Draw Dealer's First Card
    card dCard1;
    dCard1.val = generateRandomCard();
    dCard1.suit = cardSuit();
    if (dCard1.val > 10) {
      dCard1.face = faceCard(dAceCount, dCard1.val);
    }
    
    //Draw Dealer's Second Card
    card dCard2;
    dCard2.val = generateRandomCard();
    dCard2.suit = cardSuit();
    if (dCard1.val > 10) {
      dCard2.face = faceCard(dAceCount, dCard2.val);
    }
    
    //Output opening Hands
    std::cout << name << "'s Hand: ";
    if (pCard1.val > 10) {
      std::cout << pCard1.face;
    } else {
      std::cout << pCard1.val;
    }
    std::cout << " of " << pCard1.suit << " , ";
    if (pCard2.val > 10) {
      std::cout << pCard2.face;
    } else {
      std::cout << pCard2.val;
    }
    
    std::cout << " of " << pCard2.suit << std::endl; 
    
    std::cout << "Dealer's Hand: ";
    if (dCard1.val > 10) {
      std::cout << dCard1.face;
    } else {
      std::cout << dCard1.val;
    }
    std::cout << " of " << dCard1.suit << " , " << "[Hidden Card]" << std::endl;
    std::cout << "Dealer Value: " << dHandVal(dAceCount, dReset, dCard1.val) << std::endl;
    
    //Player Turns
    pWin = (pVal == 21) ? 1 : 0;
    stand = 0;
    
    if (pWin == 0) {
      std::cout << "Your hand value: " << pVal << std::endl;
      advice = adviseOptimalActionOnLuck(luck, pVal, dCard1.val, half, gChoice);
      std::cout << "The game advises you " << advice << ". ";
    }
    if (half == 1) {
      while (pVal < 21 && stand == 0) {
        std::cout <<"\nWould you like to Hit (h), Stand (s), or Double Down (d)? (h/s/d): ";
        std::cin >> userInput;
        if (userInput == "h" || userInput == "H") {
          card newCard;
          newCard.val = generateRandomCard();
          newCard.suit = cardSuit();
          if (newCard.val > 10) {
            newCard.face = faceCard(pAceCount, newCard.val);
          }
          std::cout << "You Drew a ";
          if (newCard.val > 10) {
            std::cout << newCard.face;
          } else {
            std::cout << newCard.val;
          }
          std::cout << " of " << newCard.suit << std::endl;
          pVal = pHandVal(pAceCount, pReset, pVal, newCard.val);
          std::cout << "Player hand worth: " << pVal << std:: endl;
          if (first == 1) {
            pChoice = 1;
          } 
        } else if (userInput == "s" || userInput == "S") {
          stand = 1;
          if (first == 1) {
            pChoice = 2;
          } 
        } else if (userInput == "d" || userInput == "D") {
            card newCard;
            newCard.val = generateRandomCard();
            newCard.suit = cardSuit();
            if (newCard.val > 10) {
              newCard.face = faceCard(pAceCount, newCard.val);
            }
            std::cout << "You Drew a ";
            if (newCard.val > 10) {
              std::cout << newCard.face;
            } else {
              std::cout << newCard.val;
            }
            std::cout << " of " << newCard.suit << std::endl;
            doubleDown = 1;
            stand = 1;
            if (first == 1) {
            pChoice = 3;
            } 
            pVal = pHandVal(pAceCount, pReset, pVal, newCard.val);
            std::cout << "Player hand worth: " << pVal << std:: endl;
          } else {
            std::cout << "That is not a valid option. ";
        }
        first = 0;
      }
    } else {
      while (pVal < 21 && stand == 0) {
        std::cout << "\nWould you like to Hit (h) or Stand (s)? (h/s): ";
        std::cin >> userInput;
        if (userInput == "h" || userInput == "H") {
          card newCard;
          newCard.val = generateRandomCard();
          newCard.suit = cardSuit();
          if (newCard.val > 10) {
            newCard.face = faceCard(pAceCount, newCard.val);
          }
          std::cout << "You Drew a ";
          if (newCard.val > 10) {
            std::cout << newCard.face;
          } else {
            std::cout << newCard.val;
          }
          std::cout << " of " << newCard.suit << std::endl;
          pVal = pHandVal(pAceCount, pReset, pVal, newCard.val);
          std::cout << "Player hand worth: " << pVal << std:: endl;
          if (first == 1) {
            pChoice = 1;
          } 
        } else if (userInput == "s" || userInput == "S") {
          stand = 1;
          if (first == 1) {
            pChoice = 2;
          } 
        } else {
          std::cout << "That is not a valid option. ";
        }
        first = 0;
      }
    }
    
    if (isBlackjack(pVal) == 1) {
      if (isBlackjack(dVal + dCard2.val) == 1) {
        std::cout << "You and the Dealer both god blackjack! It's a tie!" << std::endl;
        bjTies++;
        pTie = 1;
      } else {
        std::cout << "You won with a blackjack!" << std::endl;
        bjWins++;
        pWin = 1;
        pBjWin = 1;
      }
    } else if (pVal < 21) {
        std::cout << "Dealer's Turn: " << std::endl;
        dVal = dealerTurn(dCard1.val, dCard2.val, dReset, dAceCount);
        if (pVal > dVal) {
          if (dVal == 0) {
            std::cout << "Dealer broke, you win!" << std::endl;
          } else {
            std::cout << "Dealer stands at " << dVal << " you win!" << std::endl;
          }
          wins++;
          pWin = 1;
        } else if (isBlackjack(dVal) == 1) {
          std::cout << "Dealer got a blackjack! " << " you lose." << std::endl;
          bjLosses++; 
        } else if (pVal < dVal) {
          std::cout << "Dealer stands at " << dVal << " you lose." << std::endl;
          losses++;
        } else {
          std::cout << "You and the dealer tied!" << std::endl;
          ties++;
          pTie = 1;
        }
    } else {
      std::cout << "You broke." << std::endl;
      losses++;
    } 
    if (pTie == 0) {
      balance = updatePlayerBalance(balance, wager, bonus, doubleDown, pChoice, gChoice, pWin, pBjWin);
    }
    do {
      std::cout << "\nWould you like to play again? (Y/N):";
      std::cin >> play; 
      if (play == 'Y' || play == 'y') {
        replay = 1;
        rounds++;
      } else if (play == 'N' || play == 'n') {
        replay = 0;
      } else {
        play = 'x';
      }
    } while (play == 'x');
    
    if (balance <= 0) {
      balance = 0;
    }
  } while (replay == 1 && balance > 0);
  
  displayGameSummary(rounds, wins, bjWins, losses, bjLosses, ties, bjTies, startBalance, balance);
  return 0;
}
