#include "scores.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::string Scores::_scoresFileName;

Scores::Scores(std::string scorePath)
{
    _scoresFileName = scorePath + "/scores.txt";
    readScores();
}

Scores::Scores()
{
    readScores();
}

void Scores::sortScores()
{
  std::map<std::string, int>::iterator it;
  _sortVector.clear();
  for (it = _scoreMap.begin(); it != _scoreMap.end(); it++) 
  {
    _sortVector.push_back(make_pair(it->first, it->second));
  }

  std::sort(_sortVector.begin(), _sortVector.end(),
              [] (const auto &x, const auto &y) { return ((x.second > y.second) && (x.first > y.first)); });
}

void Scores::printScores() 
// print the high score list sorted by points to the terminal 
{  
  if (_scoreMap.empty()) 
  {
      std::cout << std::endl << "No high scores saved yet" << std::endl << "Nothing to print" << std::endl;
      return;
  } 
  sortScores();
  std::cout << std::endl << std::left << std::setw(6) << " RANK" << " | " << std::setw(17) << "USER" << " | " << std::setw(6) << std::right << "POINTS" << std::endl;
  for (int i = 0; i < _sortVector.size() && i < 10; i++) 
  {
   decryptUserName(_sortVector[i].first);
    std::cout << std::right << std::setw(6) << std::to_string(i + 1) + "  " << " | " << std::left << std::setw(17) << _sortVector[i].first << " | " << std::right << std::setw(4) << _sortVector[i].second << std::endl;
  }
  std::cout << std::endl;
}

void Scores::addUser(std::unique_ptr <User> usrPtr) 
{
  std::string userName = "";
  char feedback = 'n';
  std::map<std::string, int>::iterator it;

  while (feedback == 'n')
  {
    usrPtr->askForNewUser();
    userName = usrPtr->GetUserName();
    userName.resize(16, ' ');
    encryptUserName(userName);
    it = _scoreMap.find(userName);
    if (it != _scoreMap.end()) // given user name already in the high score list
    {
      std::cout << "This name is already used, do you want to override? YES [y] / NO [n]\n";
      while (true)
      {
        std::cin >> feedback;
        if (feedback == 'y' || feedback == 'n')
        { 
          break;
        }
        else
        {
          std::cout << std::endl << "Only [y] or [n] as input allowed. Please type again" << std:: endl;
        }
      }
      if (feedback == 'y') 
      {
        break;        } 
      }
    else
    {
      break;
    }
  }
  _scoreMap[userName] = usrPtr->GetUserScore();
  saveScores();
  return; // heap memory of the pointer will be freed because unique pointer goes out of scope
}


 

void Scores::readScores()
{
    std::string line;
    std::string playerName;
    int playerScore;

    _scoreMap.clear();
    std::ifstream filestream(_scoresFileName); //open the high score file
    if (filestream.is_open()) // high score file exist
    {
        while (std::getline(filestream, line))
        {
            std::istringstream linestream(line);
            while (linestream >> playerName >> playerScore)
            {
                //decrypt(playerName);
                _scoreMap.insert(std::make_pair(playerName, playerScore));
            }
        }
        filestream.close();
        //std::cout << "finishing reading file ..." << std::endl;
        return;
    }
    else // no high score file found
    {
        std::ofstream outfile(_scoresFileName);
        outfile.close();
        std::cout << "High score file did not exist. Empty file created." << std::endl;
    }
}



void Scores::saveScores() 
//write the high scores to the file
{
  std::ofstream outputFile(_scoresFileName, std::ofstream::out);
  std::map<std::string, int>::iterator it;
  for (it = _scoreMap.begin(); it != _scoreMap.end(); it++) 
  {
    //encryptedUser = Scores::encrypt(it->first);
    outputFile << it->first << " " << it->second << "\n";
  }
  outputFile.close();
}

void Scores::encryptUserName(std::string &orgString)
// encrypt the Names in the high score file
{
    int charSize = orgString.length();
    char arr[charSize];

    strcpy(arr, orgString.c_str()); 
    for(int i = 0; i < charSize; i++)
        arr[i] = arr[i] + 2;
    std::string encryptedString(arr);
    orgString = encryptedString;
    return;
}

void Scores::decryptUserName(std::string &crypString)
//decrypt user names of the high score list
{
    int charSize = crypString.length();
    char arr[charSize];

    strcpy(arr, crypString.c_str()); 
    for(int i = 0; i < charSize; i++)
        arr[i] = arr[i] - 2;
    std::string decryptedString(arr);
    crypString = decryptedString;
    return;
}