#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
  void HandleInput(bool &running, Snake &snake) const;
  //bool HandleInput(bool &running, Snake &snake) const;

 private:
    void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;

    void PauseGame(Snake& snake) const;
};

#endif