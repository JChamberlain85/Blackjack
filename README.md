# Blackjack

## Overview
This project is a simplified simulation of the Blackjack card game, implemented in C++. The game features a single player competing against a computer dealer. It aims to provide an engaging programming exercise while emphasizing responsible gaming principles.

---

## Features

### 1. **Starting the Game**
- The player is prompted to enter their name, after which they receive a randomly generated starting balance (range: $12.00 to $7000.00, inclusive). The balance is displayed with two decimal places to represent cents.

### 2. **Game Setup**
- A simulated deck of cards includes all standard card values and suits, but with infinite copies of each card.
  - **Card Values**: 
    - 2–10: Face value  
    - Jack, Queen, King: 10  
    - Ace: 1 or 11 (player's choice)
  - Suits (Hearts, Diamonds, Clubs, Spades) are randomly assigned to each card.
- Uniqueness of cards is not enforced since duplicates are allowed.

---

### 3. **Gameplay Mechanics**

#### **Wagering**
- At the start of each round, the player places a wager, ensuring it does not exceed their current balance.

#### **Dealing Hands**
- Two cards are dealt to both the player and the dealer:
  - Player’s cards are fully visible.
  - One of the dealer's cards remains hidden until their turn.

#### **Blackjack Check**
- A Blackjack (Ace + 10-value card) is identified immediately after dealing:
  - Player Blackjack wins unless both player and dealer have Blackjack (tie).
  - Dealer Blackjack results in a player loss.

#### **Player’s Turn**
- The player can:
  - **Hit**: Request additional cards until they either stand or their hand exceeds 21 (bust).
  - **Double Down**: Double the wager and receive one additional card, after which no further actions are allowed.

#### **Dealer’s Turn**
- The dealer reveals their hidden card and follows fixed rules:
  - Hit if the total is 16 or less.
  - Stand on 17 or higher.
  - Bust if their total exceeds 21.

#### **Determining the Winner**
- If neither the player nor dealer busts, the hand totals are compared:
  - Closest to 21 wins.
  - Tie results in the return of the player's wager.

---

### 4. **Continuous Play**
- After each round:
  - The player can choose to continue or exit the game.
  - The game ends automatically if the player’s balance depletes.

### 5. **Game Summary**
- Upon exiting, the program displays a summary of the player’s performance, including total rounds played, hands won, and final balance.
