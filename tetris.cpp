#include "tetris.h"

// Function to capture a keypress without echoing it to the console
char keypress() {
  // Set terminal to raw mode to capture individual keypress
  auto tempA = system("/bin/stty raw");
  char c;
  // Disable terminal echo to prevent keypress from being displayed
  auto tempB = system("/bin/stty -echo");
  // Read the keypress from standard input
  c = getc(stdin);
  // Restore terminal echo and cooked mode
  auto tempC = system("/bin/stty echo");
  auto tempD = system("/bin/stty cooked");
  return c + tempA + tempB + tempC + tempD;
}

// Check if the block is regular
bool block::isReg() const { return bReg; }

// Get the color of the block
char block::getColor() const { return color; }

// Get the position of the block
coord block::getPos() const { return pos; }

// Get the fill array of the block
coord *block::getFill() const { return fill; }

// Rotate a given point clockwise
coord block::rotator(coord point) { return {2 - point.y, point.x}; }

// Rotate a given point counterclockwise
coord block::rotatorR(coord point) { return {point.y, 2 - point.x}; }

// Perform a move and check if it's valid
bool block::performMove(void (*move)(block &, int), int count, block **brd,
                        int width, int height) {
  // Create a temporary block to simulate the move
  block temp = *this;
  // Execute the move on the temporary block
  move(temp, count);

  // Check if the move is within the boundaries and doesn't collide with other
  // blocks
  for (int i = 0; i < 4; i++) {
    if (temp.pos.x + temp.fill[i].x < 0 ||
        temp.pos.x + temp.fill[i].x >= width) {
      return false;
    }

    if (temp.pos.y + temp.fill[i].y < 0 ||
        temp.pos.y + temp.fill[i].y >= height) {
      return false;
    }

    if (brd[temp.pos.x + temp.fill[i].x][temp.pos.y + temp.fill[i].y].color !=
        'e') {
      return false;
    }
  }

  // If the move is valid, update the current block with the move
  move(*this, count);
  return true;
}

// Constructor for a block with specified position and rotation
block::block(coord pos, int rotation) : rotation(rotation), pos(pos) {
  fill = new coord[4];
  bReg = false;
  rotate(*this, rotation);
}

// Default constructor for a block
block::block() {
  fill = new coord[4];
  bReg = false;
}

// Constructor for a regular block with specified position
reg::reg(coord pos) : block(pos, 0) {
  fill[0] = {0, 0};
  fill[1] = {0, 0};
  fill[2] = {0, 0};
  fill[3] = {0, 0};
  color = 'e';
  bReg = true;
}

// Constructor for a regular block with specified position and color
reg::reg(coord pos, char color) : block(pos, 0) {
  fill[0] = {0, 0};
  fill[1] = {0, 0};
  fill[2] = {0, 0};
  fill[3] = {0, 0};
  this->color = color;
  bReg = true;
}

// Default constructor for a regular block
reg::reg() : block({0, 0}, 0) {}

// Override rotator functions for a regular block
coord reg::rotator(coord point) { return point; }
coord reg::rotatorR(coord point) { return point; }

// Set the position of a regular block
void reg::setPos(coord pos) { this->pos = pos; }

// Constructor for a Line block with specified position and rotation
Line::Line(coord pos, int rotation) : block(pos, rotation) {
  fill[0] = {0, 1};
  fill[1] = {1, 1};
  fill[2] = {2, 1};
  fill[3] = {3, 1};
  color = 'b';
}

// Override rotator functions for a Line block
coord Line::rotator(coord point) { return {3 - point.y, point.x}; }
coord Line::rotatorR(coord point) { return {point.y, 3 - point.x}; }

// Constructor for an L block with specified position and rotation
L::L(coord pos, int rotation) : block(pos, rotation) {
  fill[0] = {0, 0};
  fill[1] = {0, 1};
  fill[2] = {1, 1};
  fill[3] = {2, 1};
  color = 'w';
}

// Constructor for an inverted L block with specified position and rotation
LInvert::LInvert(coord pos, int rotation) : block(pos, rotation) {
  fill[0] = {2, 0};
  fill[1] = {0, 1};
  fill[2] = {1, 1};
  fill[3] = {2, 1};
  color = 'o';
}

// Constructor for a Square block with specified position and rotation
Square::Square(coord pos, int rotation) : block(pos, rotation) {
  fill[0] = {1, 0};
  fill[1] = {2, 0};
  fill[2] = {1, 1};
  fill[3] = {2, 1};
  color = 'y';
}

// Override rotator functions for a Square block
coord Square::rotator(coord point) { return point; }
coord Square::rotatorR(coord point) { return point; }

// Constructor for a Z block with specified position and rotation
Z::Z(coord pos, int rotation) : block(pos, rotation) {
  fill[0] = {1, 0};
  fill[1] = {2, 0};
  fill[2] = {0, 1};
  fill[3] = {1, 1};
  color = 'g';
}

// Constructor for a T block with specified position and rotation
T::T(coord pos, int rotation) : block(pos, rotation) {
  fill[0] = {1, 0};
  fill[1] = {0, 1};
  fill[2] = {1, 1};
  fill[3] = {2, 1};
  color = 'p';
}

// Constructor for an inverted Z block with specified position and rotation
ZInvert::ZInvert(coord pos, int rotation) : block(pos, rotation) {
  fill[0] = {0, 0};
  fill[1] = {1, 0};
  fill[2] = {1, 1};
  fill[3] = {2, 1};
  color = 'r';
}

// function to check spawn conditions of a block on a specific board array
bool checkSpawnConditions(block &blc, block **brd, int width, int height) {
  block temp = blc;

  for (int i = 0; i < 4; i++) {
    // Check if the block is within the vertical bounds of the board
    if (temp.pos.y + temp.fill[i].y >= height ||
        temp.pos.y + temp.fill[i].y < 0)
      return false;

    // Check if the block is within the horizontal bounds of the board
    if (temp.pos.x + temp.fill[i].x >= width || temp.pos.x + temp.fill[i].x < 0)
      return false;

    // Check if the target position on the board is already occupied
    if (brd[temp.pos.x + temp.fill[i].x][temp.pos.y + temp.fill[i].y].color !=
        'e')
      return false;
  }

  return true;
}

board::board() {
  // Initialize the game board
  brd = new block *[width];
  for (int i = 0; i < width; i++) {
    brd[i] = new reg[height];
  }

  // Fill the game board with regular blocks
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      brd[i][j] = reg({i, j});
    }
  }

  // Initialize the preview board for upcoming blocks
  nextBlockBrd = new block *[6];
  for (int i = 0; i < 6; i++) {
    nextBlockBrd[i] = new reg[8];
  }

  // Fill the preview board with regular blocks
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 8; j++) {
      nextBlockBrd[i][j] = reg({i, j});
    }
  }

  // Generate the first upcoming block randomly
  switch (rand() % 7) {
  case 0:
    nextBlock = Line({3, 3}, 0);
    break;
  case 1:
    nextBlock = L({3, 3}, 0);
    break;
  case 2:
    nextBlock = LInvert({3, 3}, 0);
    break;
  case 3:
    nextBlock = Square({3, 3}, 0);
    break;
  case 4:
    nextBlock = Z({3, 3}, 0);
    break;
  case 5:
    nextBlock = T({3, 3}, 0);
    break;
  case 6:
    nextBlock = ZInvert({3, 3}, 0);
  }

  // Summon the first block to the game board
  summonBlock();
}

board board::operator=(const board &b) {
  // Copy the contents of the game board
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      this->brd[i][j] = b.brd[i][j];
    }
  }

  // Copy other attributes of the game board
  this->curBlock = b.curBlock;
  this->nextBlock = b.nextBlock;
  this->level = b.level;
  this->score = b.score;
  return *this;
}

void board::scoreTracking() {
  bool streak = false;
  static int streakCount = 0;
  bool rowCheck[height];

  // Initialize the row check array
  for (int i = 0; i < height; i++)
    rowCheck[i] = true;

  // Check each row to see if it's full
  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
      if (brd[j][i].getColor() == 'e')
        rowCheck[i] = false;

  // Check if there's a full row
  for (int i = 0; i < height; i++)
    if (rowCheck[i])
      streak = true;

  // If no streak, reset the streak count
  if (!streak)
    streakCount = 0;

  // Clear full rows and update the game state
  for (int i = 0; i < height; i++)
    if (rowCheck[i]) {
      for (int j = 0; j < width; j++)
        brd[j][i] = reg({j, i});

      this_thread::sleep_for(chrono::milliseconds(min(tickInterval(), 1000)));

      // Shift rows down after clearing a row
      for (int j = i; j > 0; j--)
        for (int k = 0; k < width; k++)
          brd[k][j + 1] = brd[k][j];

      linesCleared++;
      streakCount++;
    }

  // Update the game level
  updateLevel();

  // Update the score based on the streak
  for (int i = 1; i <= streakCount; i++)
    score += tgamma(i + 1) * (level + 1) * 100;
}

void board::summonBlock() {
  // Generate a new block based on the color of the next block
  switch (nextBlock.getColor()) {
  case 'b':
    do {
      nextBlock = Line({rand() % (width + 4) - 2, 0}, 0);
    } while (!checkSpawnConditions(nextBlock, brd, width, height));
    break;
  case 'w':
    do {
      nextBlock = L({rand() % width, 0}, 0);
    } while (!checkSpawnConditions(nextBlock, brd, width, height));
    break;
  case 'o':
    do {
      nextBlock = LInvert({rand() % width, 0}, 0);
    } while (!checkSpawnConditions(nextBlock, brd, width, height));
    break;
  case 'y':
    do {
      nextBlock = Square({rand() % width, 0}, 0);
    } while (!checkSpawnConditions(nextBlock, brd, width, height));
    break;
  case 'g':
    do {
      nextBlock = Z({rand() % width, 0}, 0);
    } while (!checkSpawnConditions(nextBlock, brd, width, height));
    break;
  case 'p':
    do {
      nextBlock = T({rand() % width, 0}, 0);
    } while (!checkSpawnConditions(nextBlock, brd, width, height));
    break;
  case 'r':
    do {
      nextBlock = ZInvert({rand() % width, 0}, 0);
    } while (!checkSpawnConditions(nextBlock, brd, width, height));
    break;
  }

  // Set the current block to the new block
  curBlock = nextBlock;

  // Generate the next upcoming block randomly

  switch (rand() % 7) {
  case 0:
    nextBlock = Line({1, 3}, 0);
    break;
  case 1:
    nextBlock = L({3, 3}, 0);
    break;
  case 2:
    nextBlock = LInvert({3, 3}, 0);
    break;
  case 3:
    nextBlock = Square({3, 3}, 0);
    break;
  case 4:
    nextBlock = Z({3, 3}, 0);
    break;
  case 5:
    nextBlock = T({3, 3}, 0);
    break;
  case 6:
    nextBlock = ZInvert({3, 3}, 0);
  }
}

void shiftD(block &blc, int count) {
  // Shift the block downward by the specified count
  blc.pos.y += count;
}

void shiftR(block &blc, int count) {
  // Shift the block to the right by the specified count
  blc.pos.x += count;
}

void shiftL(block &blc, int count) {
  // Shift the block to the left by the specified count
  blc.pos.x -= count;
}

void rotate(block &blc, int rotation) {
  if (rotation == 0) {
    return;
  } else {
    // Rotate the block based on the specified rotation
    for (int i = 0; i < abs(rotation); i++) {
      coord *temp = blc.fill;
      blc.fill = new coord[4];
      for (int j = 0; j < 4; j++) {
        // Use rotator or rotatorR based on the rotation direction
        if (rotation > 0)
          blc.fill[j] = blc.rotator(temp[j]);
        else
          blc.fill[j] = blc.rotatorR(temp[j]);
      }
    }
  }

  blc.rotation += rotation;
  blc.rotation = blc.rotation % 4;
}

void board::fastTrack() {
  // Skip ticks for a short duration
  tickless();
  this_thread::sleep_for(chrono::milliseconds(min(tickInterval(), 1000)));
  cin.clear();
}

void blockDegen(const block &blc, block **brd, int width, int height) {
  block temp = blc;
  for (int i = 0; i < 4; i++) {
    // Convert block to regular blocks on the board
    brd[temp.getPos().x + temp.getFill()[i].x]
       [temp.getPos().y + temp.getFill()[i].y] =
           reg({temp.getPos().x + temp.getFill()[i].x,
                temp.getPos().y + temp.getFill()[i].y},
               temp.getColor());
  }
}

ostream &operator<<(ostream &out, const board &brd) {
  // Create a copy of the board for drawing
  board drawing;
  drawing = brd;
  // Convert the current block to regular blocks on the board
  blockDegen(drawing.curBlock, drawing.brd, brd.width, brd.height);

  // Print the top border of the game display
  cout << "+--------------------+----------------+" << endl;
  // Print the score and level information
  out << "|Score ";
  out << left << setw(5) << drawing.score;
  out << " Level ";
  out << setw(2) << drawing.level;
  out << "|   Next Block   |" << endl;
  // Print the middle border of the game display
  out << "+--------------------+----------------+" << endl;

  // Convert the upcoming block to regular blocks on the preview board
  blockDegen(drawing.nextBlock, drawing.nextBlockBrd, 6, 8);

  // Print the game board and upcoming block preview
  for (int i = 0; i < 8; i++) {
    // Print left border for the game board
    out << '|';
    for (int j = 0; j < brd.width; j++)
      if (drawing.brd[j][i + 4].getColor() == 'e')
        out << "  "; // Empty cell
      else
        out << "[]"; // Occupied cell
    // Print separator and left border for the upcoming block preview
    out << '|';
    for (int j = 0; j < 6; j++)
      if (drawing.nextBlockBrd[j][i].getColor() == 'e')
        out << "  "; // Empty cell
      else
        out << "[]"; // Occupied cell
    // Print right border and separator
    out << "    |" << endl;
  }

  // Print the bottom borders for the game board
  out << '|';
  for (int i = 0; i < brd.width; i++)
    if (drawing.brd[i][12].getColor() == 'e')
      out << "  ";
    else
      out << "[]";
  out << "+----------------+" << endl;

  out << '|';
  for (int i = 0; i < brd.width; i++)
    if (drawing.brd[i][13].getColor() == 'e')
      out << "  ";
    else
      out << "[]";
  out << "| Recent Scores  |" << endl;

  out << '|';
  for (int i = 0; i < brd.width; i++)
    if (drawing.brd[i][14].getColor() == 'e')
      out << "  ";
    else
      out << "[]";
  out << "+----------------+" << endl;

  // Print recent scores and usernames
  for (int i = 15; i < brd.height; i++) {
    out << '|';
    for (int j = 0; j < brd.width; j++) {
      if (drawing.brd[j][i].getColor() == 'e')
        out << "  "; // Empty cell
      else
        out << "[]"; // Occupied cell
    }
    out << "| ";
    // Print usernames and scores with proper formatting
    if (static_cast<int>(brd.usernames.size()) + 14 - i >= 0)
      out << setw(7) << left
          << brd.usernames[static_cast<int>(brd.usernames.size()) + 14 - i];
    else
      out << "       " << left;
    out << ' ';
    if (static_cast<int>(brd.scores.size()) + 14 - i >= 0)
      out << setw(6) << right
          << brd.scores[static_cast<int>(brd.scores.size()) + 14 - i];
    else
      out << "      " << left;
    // Print separators
    out << " |";
    out << endl;
  }

  // Print the bottom border of the game display
  out << "+--------------------+----------------+" << endl;
  return out;
}

// update board 1 time (1 tick)
void board::tick() {
  // Update the score and check if the current block can move down
  scoreTracking();
  if (!curBlock.performMove(shiftD, 1, brd, width, height)) {
    // If the block can't move down, convert it to regular blocks and summon a
    // new block
    blockDegen(curBlock, brd, width, height);
    summonBlock();
  }
  auto temp [[maybe_unused]] = system("clear");
  cout << *this;
}

// fasttrack board
void board::tickless() {
  // Move the current block downward until it can't move anymore
  while (curBlock.performMove(shiftD, 1, brd, width, height))
    ;
}

bool board::lossCheck() {
  // Check if any block in the top row is occupied, indicating game loss
  for (int i = 0; i < width; i++)
    if (brd[i][4].getColor() != 'e')
      return true;
  return false;
}

int board::tickInterval() {
  // Return the tick interval based on the current level
  switch (level) {
  case 1:
    return 1000;
    break;
  case 2:
    return 793;
    break;
  case 3:
    return 618;
    break;
  case 4:
    return 473;
    break;
  case 5:
    return 355;
    break;
  case 6:
    return 262;
    break;
  case 7:
    return 190;
    break;
  case 8:
    return 135;
    break;
  case 9:
    return 94;
    break;
  case 10:
    return 64;
    break;
  case 11:
    return 43;
    break;
  case 12:
    return 28;
    break;
  case 13:
    return 18;
    break;
  case 14:
    return 11;
    break;
  case 15:
    return 7;
    break;
  default:
    throw "invalid level";
  }
}

void board::updateLevel() {
  // Update the game level based on the number of lines cleared
  level = 1 + linesCleared / 10;
}

string displayMainMenu() {
  string username;
  cout << "Welcome to Tetris!\n";

  // Loop until a valid username is provided
  while (true) {
    cout << "Enter your username (between 1 and 7 characters): ";
    getline(cin, username);

    // Perform error checking on the username
    if (!username.empty() && username.length() <= 7) {
      break; // Exit the loop if a valid username is provided
    } else {
      cout << "Invalid username. Please try again (between 1 and 7 "
              "characters)\n";
    }
  }

  return username;
}
