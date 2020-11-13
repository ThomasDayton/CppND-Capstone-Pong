#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "paddle.h"

void Controller::ChangeDirection(Paddle &paddle, Paddle::Direction input) const {
  paddle.direction[input] = true;
  paddle.moving = true;
  return;
}

void Controller::StopMovement(Paddle &paddle, Paddle::Direction input) const {
  paddle.direction[input] = false;
  paddle.moving = false;
  return;
}

void Controller::HandleInput(bool &running, Paddle &paddleOne, Paddle &paddleTwo) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_w:
          ChangeDirection(paddleOne, Paddle::Direction::kUp);
          //break;

        case SDLK_s:
          ChangeDirection(paddleOne, Paddle::Direction::kDown);
          //break;

        case SDLK_UP:
          ChangeDirection(paddleTwo, Paddle::Direction::kUp);
          //break;

        case SDLK_DOWN:
          ChangeDirection(paddleTwo, Paddle::Direction::kDown);
          //break;
      }
    } else if (e.type == SDL_KEYUP) {
      switch (e.key.keysym.sym) {
        case SDLK_w:
          StopMovement(paddleOne, Paddle::Direction::kUp);
          //break;
        case SDLK_s:
          StopMovement(paddleOne, Paddle::Direction::kDown);
          //break;
        case SDLK_UP:
          StopMovement(paddleTwo, Paddle::Direction::kUp);
          //break;
        case SDLK_DOWN:
          StopMovement(paddleTwo, Paddle::Direction::kDown);
          //break;
      }
    }
  }
}