#ifndef UserInterface_H
#define UserInterface_H

enum GameStatus {play, score, quit};

class UserInterface {
public:
UserInterface();
void ChoiceMenu();
GameStatus GetGameStatus();
private:
GameStatus _gameSatusFlag;
};

#endif