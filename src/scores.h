#ifndef SCORES_H
#define SCORES_H

#include <map>
#include <string>
#include <vector>
#include <unistd.h>
#include <memory>
#include "users.h"

class Scores {
public:
  Scores();
  Scores(std::string scoresPath);
  void addUser(std::unique_ptr <User> usrPtr);
  void printScores();
  void setScoresFileName(std::string fileName);

private:
  std::map<std::string, int> _scoreMap;
  static std::string _scoresFileName;
  std::vector<std::pair<std::string, int> > _sortVector; 
  void readScores();
  void sortScores();
  void saveScores();
  void encryptUserName(std::string &orgString);
  void decryptUserName(std::string &crypString);
};


#endif