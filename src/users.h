#ifndef Users_H
#define Users_H

#include <string>

using std::string;

class User
{

public:
    User();
    void askForNewUser();
    string GetUserName();
    void SetUserName(string name);
    int GetUserScore();
    void SetUserScore(int points);
private:
    string _userName;
    int _userScore;

};

#endif