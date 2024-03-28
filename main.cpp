#include "tetris.h"
#include <fstream>
#include <unistd.h>

board b;

// Function prototypes
void shiftR(block &blc, int count);
void shiftL(block &blc, int count);
void rotate(block &blc, int count);

// Function to set timeout for a given function
void setTimeout(function<void()> func, int milli) {
  while (!b.lossCheck()) {
    this_thread::sleep_for(chrono::milliseconds(milli));
    func();
  }
}

// Function to handle user input during the game
void inputHandler() {
  switch (keypress()) {
    case 'd':
      b.curBlock.performMove(shiftR, 1, b.brd, b.width, b.height);
      break;
    case 'a':
      b.curBlock.performMove(shiftL, 1, b.brd, b.width, b.height);
      break;
    case 'c':
      b.curBlock.performMove(rotate, 1, b.brd, b.width, b.height);
      break;
    case 'z':
      b.curBlock.performMove(rotate, -1, b.brd, b.width, b.height);
      break;
    case ' ':
      b.fastTrack();
  }
  auto temp [[maybe_unused]] = system("clear");
  cout << b;
}

// Function to update user input
void updateInput() { inputHandler(); }

// Function for the ticker thread
void ticker() { b.tick(); }

// Main function
int main() {
  // Input file streams to read usernames and scores
  ifstream fin1("usernames.txt");
  ifstream fin2("scores.txt");
  string tempString;

  // Read usernames from file
  while (getline(fin1, tempString))
    b.usernames.push_back(tempString);

  // Read scores from file
  while (getline(fin2, tempString))
    b.scores.push_back(stoi(tempString));

  // Hide cursor
  cout << "\033[?25l";

  // Main Menu
  // Display main menu and get the username
  tempString = displayMainMenu();

  while(true) {
    // Countdown before starting the game
    for (int i = 3; i >= 1; i--) {
      auto temp [[maybe_unused]] = system("clear");
      cout << "STARTING TETRIS IN: ";
      cout << i << endl;
      sleep(1);
    }

    auto temp [[maybe_unused]] = system("clear");
    // Start the timeout in a separate thread
    thread timeoutThread(setTimeout, updateInput, min(b.tickInterval(), 33));
    // Start the ticker thread
    thread tickerThread(setTimeout, ticker, b.tickInterval());
    srand(time(0));

    // Wait for the game to be over
    while (!b.lossCheck());

    // Store username and score in vectors
    b.usernames.push_back(tempString);
    b.scores.push_back(b.score);

    // Store the username and score in files
    ofstream fout1("usernames.txt");
    ofstream fout2("scores.txt");

    for (int i = 0; i < b.usernames.size(); i++)
      fout1 << b.usernames[i] << endl;

    for (int i = 0; i < b.scores.size(); i++)
      fout2 << b.scores[i] << endl;

    fout1.close();
    fout2.close();

    // Wait for threads to finish
    timeoutThread.join();
    tickerThread.join();

    temp = system("clear");
    cout << "GAME OVER" << endl;
    cout << "Your score: " << b.score << endl;

    while(true) {
      // Ask user if they want to play again
      cout << "Do you want to play again? (y/n): ";
      cin >> tempString;
      if(tempString.length() == 1 && tolower(tempString[0]) == 'n')
        return 0;
      else if (tempString.length() == 1 && tolower(tempString[0]) == 'y'){
        //clear board and reset screen
        temp = system("clear");
        b = board();
        break;
      } else 
        //error message
        cout << "Incorrect option, please enter either Y or N!" << endl;
    }
  }

  return 0;
}
