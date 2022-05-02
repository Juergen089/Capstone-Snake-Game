#include <iostream>
#include <memory>
#include <filesystem>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "scores.h"
#include "userinterface.h"
#include "users.h"


int main(int argc,char *argv[]) {
  auto dir = weakly_canonical(std::filesystem::path(argv[0])).parent_path();
  std::string pt = dir.c_str();
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Scores highScores(pt);
  std::cout << "============================" << std::endl << "path : " << pt << std::endl << "============================" << std::endl;
  UserInterface userInterface;
  //start the user interfasce 
  while (userInterface.GetGameStatus() != play)
  {
    userInterface.ChoiceMenu();
    if (userInterface.GetGameStatus() == quit){ return 0;} // quit game selected
  }
  // User choice: game should be started
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Snake Game terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";

  std::unique_ptr <User> usr = std::make_unique<User>();
  usr->SetUserScore(game.GetScore());
  highScores.addUser(std::move(usr));
  return 0;
}