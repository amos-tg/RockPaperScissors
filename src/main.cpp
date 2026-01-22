#include <random>
#include <iostream>
#include <string>
#include <cctype>

/// four constants for each possible choice (0..=3)
enum { ROCK, PAPER, SCISSORS, QUIT }; 

/// generates and returns a random number x with the following guarentees: 
/// (x >= range_start && x <= range_end)
int getRandRanged(int range_start, int range_end);

int getUserChoice(void);

void compareAndTally(
    int user_choice, int computer_choice, int user_score, int comp_score);

void quitAndDisplay(int user_score, int comp_score);

int main(void) {
  int user_score, comp_score, user_choice, comp_choice;
  
  for (;;) {
    user_choice = getUserChoice();

    if (user_choice == QUIT) {
      break;
    }

    comp_choice = getRandRanged(ROCK, SCISSORS);

    compareAndTally(user_choice, comp_choice, user_score, comp_score);
  }
  
  return 0;
}

int getRandRanged(int range_start, int range_end) {
  // The purpose of the program is to generate these random responses for the
  // user, it will be doing this for the life of the program; it simplifies the
  // function if the random_device just gets stored for the life of the program.
  static std::random_device rand;
  std::uniform_int_distribution<int> distrib(range_start, range_end);

  return distrib(rand);
}

int getUserChoice(void) {
  const char *query = 
    "Rock Paper Scissors:\n- Rock\n- Paper\n- Scissors\n- Quit";
  const char *err_msg =
    "Error: invalid user input"; 

  std::cout << query << std::endl;

  std::string input; 

  std::cin >> input; 
  if (!std::cin) {
    std::cerr << err_msg << std::endl;
    exit(1);
  } 

  for (char &c: input) { 
    c = std::tolower(c);
  }

  if (input == "rock") {
    return ROCK;
  } else if (input == "paper") {
    return PAPER;
  } else if (input == "scissors") {
    return SCISSORS;
  } else if (input == "quit") {
    return QUIT;
  } else {
    std::cerr << err_msg << std::endl;
    exit(1); 
  }
}
