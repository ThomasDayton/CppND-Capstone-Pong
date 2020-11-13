#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "paddle.h"

class Controller {
 public:
  void HandleInput(bool &running, Paddle &paddleOne, Paddle &paddleTwo) const;

 private:
  void ChangeDirection(Paddle &paddle, Paddle::Direction input) const;
  void StopMovement(Paddle &paddle, Paddle::Direction input) const;
};

#endif