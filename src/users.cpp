#include <iostream>
#include <string>
#include "users.h"
#include "scores.h"

using std::string;

User::User() : _userName (""), _userScore(0){}

void User::askForNewUser()
{
  string userName;
  
  std::cout << std::endl << "Please type in your name and press Enter: [max 16 characters]" << std::endl;
  std::cin >> userName; 
  _userName = userName;
  return;
}

string User::GetUserName()
{
  return _userName;
}

void User::SetUserName(string name)
{
  _userName = name;
  return;
}

int User::GetUserScore()
{
  return _userScore;
}

void User::SetUserScore(int points)
{
  _userScore = points;
}
