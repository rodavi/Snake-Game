#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "scores.h"
#include <memory>

int main() {

  std::unique_ptr<Scores> scored = std::make_unique<Scores>("scores.txt");
  //scored->getScores("scores.txt");
  scored->getScores();

  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  //Controller controller;
  std::unique_ptr<Controller> controller = std::make_unique<Controller>();
  Game game(kGridWidth, kGridHeight);
  game.Run(*(controller.get()), renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";

  if(game.GetScore() > scored->getLast().score)
  {
    std::string new_player_name;
    std::cout<<"New Top 3 score!, please add your name: ";
    std::cin>>new_player_name;
    Player new_player;
    new_player.name = new_player_name;
    new_player.score = game.GetScore();
    scored->setScores(new_player);
    scored->printScores();
  }
  return 0;
}