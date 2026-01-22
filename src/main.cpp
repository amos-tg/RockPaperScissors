#include <random>
#include <iostream>

/// four constants for each possible choice (0..=3)
enum { ROCK, PAPER, SCISSORS, QUIT }; 

/// generates and returns a random number x with the following guarentees: 
/// (x >= 0 && x < 3), these numbers are mapped directly onto the possible
/// enum variants; computer cannot return quit/3.
int getRandRPS(void);

/// returns the users choice as an integer with the following guarentees: 
/// (x >= 0 && x <= 3), these numbers are mapped directly onto the four possible
/// enum variants.
int getUserRPS(void);

void compareAndTally(
    int user_choice, int computer_choice, int user_score, int comp_score);

void quitAndDisplay(int user_score, int comp_score);

int main(void) {
  int user_score, comp_score, user_choice, comp_choice;
  
  for (;;) {
    user_choice = getUserRPS();

    if (user_choice == QUIT) {
      break;
    }

    comp_choice = getRandRPS();

    compareAndTally(user_choice, comp_choice, user_score, comp_score);
  }
  
  return 0;
}
