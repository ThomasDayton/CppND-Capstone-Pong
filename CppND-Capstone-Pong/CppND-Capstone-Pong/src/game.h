#ifndef GAME_H
#define GAME_H

#include <random>
#include <string>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "ball.h"
#include "paddle.h"
#include "collision.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetP1Score() const;
  int GetP2Score() const;
  
  std::string GetWinner() const;

 private:
  Ball ball;
  Paddle paddleOne;
  Paddle paddleTwo;

  std::random_device dev;
  std::mt19937 engine;
  //std::uniform_int_distribution<int> random_w;
  //std::uniform_int_distribution<int> random_h;

  int playerOneScore{0};
  int playerTwoScore{0};
  
  bool paused = true; //so the ball doesn't move unless the player provides input

  void Update(float dt);
  void ResetBoard();
  
  Contact CheckPaddleCollision(Ball const& ball, Paddle const& paddle);
  
  Contact CheckWallCollision(Ball const& ball);
};

#endif