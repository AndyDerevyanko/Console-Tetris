#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include <chrono>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

// Function to get a keypress from the user
char keypress();

// Function to display the main menu and get a username
string displayMainMenu();

// Struct to represent coordinates
struct coord {
public:
  int x, y;
};

// Base class for tetris blocks
class block {
protected:
  coord *fill;
  int rotation;
  coord pos;
  char color;
  bool bReg;

public:
  bool isReg() const;

  char getColor() const;

  coord getPos() const;

  coord *getFill() const;

  // Virtual functions for rotation
  virtual coord rotator(coord point);
  virtual coord rotatorR(coord point);

  // Friend functions for block movement
  friend void shiftD(block &blc, int count);
  friend void shiftR(block &blc, int count);
  friend void shiftL(block &blc, int count);
  friend void rotate(block &blc, int rotation);

  bool performMove(void (*move)(block &, int), int count, block **brd,
                   int width, int height);

  friend bool checkSpawnConditions(block &blc, block **brd, int width,
                                   int height);

  // Constructors
  block(coord pos, int rotation);
  block();
};

// Derived class for regular blocks
class reg : public block {
public:
  reg(coord pos);
  reg(coord pos, char color);
  reg();

  // Overridden rotation functions
  coord rotator(coord point);
  coord rotatorR(coord point);

  // Setter for position
  void setPos(coord pos);
};

// Derived class for Line-shaped blocks
class Line : public block {
public:
  Line(coord pos, int rotation);

  // Overridden rotation functions
  coord rotator(coord point);
  coord rotatorR(coord point);
};

// Derived class for L-shaped blocks
class L : public block {
public:
  L(coord pos, int rotation);
};

// Derived class for inverted L-shaped blocks
class LInvert : public block {
public:
  LInvert(coord pos, int rotation);
};

// Derived class for square-shaped blocks
class Square : public block {
public:
  Square(coord pos, int rotation);

  // Overridden rotation functions
  coord rotator(coord point);
  coord rotatorR(coord point);
};

// Derived class for Z-shaped blocks
class Z : public block {
public:
  Z(coord pos, int rotation);
};

// Derived class for T-shaped blocks
class T : public block {
public:
  T(coord pos, int rotation);
};

// Derived class for inverted Z-shaped blocks
class ZInvert : public block {
public:
  ZInvert(coord pos, int rotation);
};

// Class representing the Tetris game board
class board {
public:
  int score = 0;
  int level = 1;
  int linesCleared = 0;
  block **brd; // 10 x 24
  const int width = 10, height = 24;
  block curBlock;
  block nextBlock;
  block **nextBlockBrd;
  vector<string> usernames;
  vector<int> scores;

  // Constructor
  board();

  // Assignment operator
  board operator=(const board &b);

  // Function to track and update the score
  void scoreTracking();

  // Overloaded output operator for board
  friend ostream &operator<<(ostream &out, const board &b);

  // Function to summon a new block
  void summonBlock();

  // Function to advance the game by one tick
  void tick();

  // Function to check if the game has ended
  bool lossCheck();

  // Function for handling user input during the game
  void inputHandler();

  // Function to update user input
  void updateInput();

  // Function to calculate the tick interval based on the current level
  int tickInterval();

  // Function to update the game level
  void updateLevel();

  // Function to simulate a tick without updating the display
  void tickless();

  // Function to fast-track the block to the bottom
  void fastTrack();
};

#endif // TETRIS_GAME_H
