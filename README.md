# Chess Game

## Game Modes
After launching the program, you'll be prompted to choose a mode:  
1 – Player vs Computer  
2 – Computer vs Computer  
3 – Player vs Player  

In Player vs Computer mode, you can also choose whether to play white or black.

---

## AI Logic – Best Move Recommendation

### Search Algorithm
The AI uses a Minimax algorithm with configurable depth. It supports:
- Alpha-beta pruning  
- Multithreaded evaluation via a ThreadPool  
- Early stopping based on a score threshold  

---

### Priority Queue
A custom `PriorityQueue<Move>` is used to maintain and sort the best moves:
- Holds up to the top 5 moves based on the move score  
- Computer randomly chooses 1 of the top 3 moves to simulate realistic play  

---

#### Example Scores:
- Capturing a Queen: +50  
- Capturing a Rook: +30  
- Delivering checkmate: +1000  

---

## Features
- Castling (both kingside and queenside)  
- Move legality checking  
- Randomized AI moves from top 3 options  
- checkmate detection  
- Player vs AI, AI vs AI, and Player vs Player support  

---

## Exceptions
The system uses custom exceptions for:
- `InvalidMoveException`: When a move is not legal  
- `PromotionException`: Invalid piece type for pawn promotion  

---

## Testing and Challenges

### How we tested the code:
- Manual input testing in **Player vs Player** and **Player vs AI** modes  
- Edge-case testing for castling, promotion, and checkmate  
- Printed debug outputs for each stage of move execution  

###  Short edge cases covered:
- Invalid input (same source and destination)  
- Illegal moves blocked 

###  Biggest challenge:
- Implementing multithreaded Minimax with a shared thread pool safely  
- Handling early stopping conditions and making sure they propagate correctly  

###  Improvements if more time was available:
 Better graphics or GUI support  
---

## How to Compile and Run

```bash
cd src
g++ -std=c++17 -pthread -I ../include -o chess *.cpp
./chess
```
