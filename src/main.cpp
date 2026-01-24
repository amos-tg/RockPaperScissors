#include <random>
#include <iostream>
#include <string>
#include <cctype>

/// four constants for each possible choice (0..=3)
enum { ROCK, PAPER, SCISSORS, QUIT }; 

/// generates and returns a random number x with the following guarentees: 
/// (x >= range_start && x <= range_end)
int getRandRanged(int range_start, int range_end);

/// gets the users choice, validates it, and returns it as an integer 
/// with the following guarentees made of the return value:
/// (x >= ROCK(0) && x <= QUIT(3))
int getUserChoice(void);

/// Takes the user and computer choices for one round of rock paper
/// scissors, determines the winner, and then adds to the
/// score of the winner. 
void scoreRound(
    int user_choice, int computer_choice, int &user_score, int &comp_score);

/// user_score: the user score which gets printed.
///
/// comp_score: the computers score which gets printed.
///
/// Displays the scores the user and the computer have. 
void displayScores(int user_score, int comp_score);

/// user_score: the user score which determines the winner.
///
/// comp_score: the computers score which determines the winner.
///
/// Displays the winner of the tournament.
void declareWinner(int user_score, int comp_score);


int main(void) {
  int user_score {}, comp_score {}, user_choice, comp_choice;
  
  for (;;) {
    user_choice = getUserChoice();

    if (user_choice == QUIT) {
      break;
    }

    comp_choice = getRandRanged(ROCK, SCISSORS);

    scoreRound(user_choice, comp_choice, user_score, comp_score);

    // The directions don't say to show the scores after each round but I think
    // it would look nice
    displayScores(user_score, comp_score);
  }
  
  displayScores(user_score, comp_score);
  declareWinner(user_score, comp_score);

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
    "\nRock Paper Scissors:\n\t- Rock\n\t- Paper\n\t- Scissors\n\t- Quit\nChoose: ";
  const char *err_msg =
    "Error: invalid user input"; 

  std::cout << query;
  std::cout.flush();

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

void scoreRound(
     int user_choice, int computer_choice, int &user_score, int &comp_score)
{
  // handles ties
  if (user_choice == computer_choice) {
    return; 
  }

  // handles competitive matchups
  switch (user_choice) {
  case ROCK:
    if (computer_choice == PAPER) {
      ++comp_score;      
    } else {
      ++user_score;
    }

    break;

  case PAPER:
    if (computer_choice == SCISSORS) {
      ++comp_score;
    } else {
      ++user_score;
    }

    break;

  case SCISSORS:
    if (computer_choice == ROCK) {
      ++comp_score;
    } else {
      ++user_score;
    }

    break;
  }
}

void displayScores(int user_score, int comp_score) {
  std::cout << '\n' << "Scores:" << '\n' <<
    "\t - User Score: " << user_score << '\n' <<
    "\t - Computer Score: " << comp_score << std::endl;
}

void declareWinner(int user_score, int comp_score) {
  std::string winner;

  if (user_score == comp_score) {
    winner = "Tie";
  } else if (user_score > comp_score) {
    winner = "Player";
  } else if (user_score < comp_score) {
    winner = "Computer";
  }

  std::cout << '\n' << "Tournament Winner: " << winner << std::endl;
}
