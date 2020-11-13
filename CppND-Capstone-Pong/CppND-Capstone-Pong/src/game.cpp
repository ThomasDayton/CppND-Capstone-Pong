#include "game.h"
#include <chrono>
#include <iostream>
#include <string>
#include "vec2.h"
#include "SDL.h"

Game::Game(std::size_t screen_width, std::size_t screen_height)
    : ball(Vec2((screen_width / 2.0f) - (15 / 2.0f),
          (screen_height / 2.0f) - (15 / 2.0f))),
	  paddleOne(Vec2(50.0f, (screen_height / 2.0f) - (90 / 2.0f)), Vec2(0.0f, 0.0f)),
	  paddleTwo(Vec2(screen_width - 50.0f, (screen_height / 2.0f) - (90 / 2.0f)), Vec2(0.0f, 0.0f)),
      engine(dev()) {
      //random_w(0, static_cast<int>(grid_width)),
      //random_h(0, static_cast<int>(grid_height)) {
  //PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  float dt = 0.0f;

  while (running) {
    auto startTime = std::chrono::high_resolution_clock::now();
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, paddleOne, paddleTwo);
    Update(dt);
    renderer.Render(ball, paddleOne, paddleTwo);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(playerOneScore, playerTwoScore, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
    auto stopTime = std::chrono::high_resolution_clock::now();
	dt = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime - startTime).count();
  }
}

void Game::Update(float dt) {
  if (playerOneScore >= 3 || playerTwoScore >= 3) return;

  paddleOne.Update(dt);
  paddleTwo.Update(dt);
}

int Game::GetP1Score() const { return playerOneScore; }
int Game::GetP2Score() const { return playerTwoScore; }

std::string Game::GetWinner() const 
{
  if (playerOneScore >= 3)
  {
    return "Player 1";
  } else if (playerTwoScore >= 3) {
    return "Player 2";
  } else { //this won't happen, but it never hurts to be safe
    return "Tie Game";
  }
}
//int Game::GetSize() const { return snake.size; }