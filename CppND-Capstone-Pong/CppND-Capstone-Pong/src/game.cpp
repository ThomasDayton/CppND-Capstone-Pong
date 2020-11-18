#include "game.h"
#include <chrono>
#include <iostream>
#include <string>
#include "vec2.h"
#include "SDL.h"

Game::Game(std::size_t screen_width, std::size_t screen_height)
    : ball(Vec2((screen_width / 2.0f) - (15 / 2.0f), (screen_height / 2.0f) - (15 / 2.0f)),
          Vec2(1.0f, 0.0f)),
	  paddleOne(Vec2(50.0f, (screen_height / 2.0f) - (90 / 2.0f)), Vec2(0.0f, 0.0f)),
	  paddleTwo(Vec2(screen_width - 50.0f, (screen_height / 2.0f) - (90 / 2.0f)), Vec2(0.0f, 0.0f)),
      engine(dev()) {
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
  
  renderer.UpdateWindowTitle(playerOneScore, playerTwoScore, frame_count, paused);

  while (running) {
    auto startTime = std::chrono::high_resolution_clock::now();
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, paused, paddleOne, paddleTwo);
    if (paused) 
    { 
      //renderer.UpdateWindowTitle(playerOneScore, playerTwoScore, frame_count, paused);
      continue; 
    }
    Update(dt);
    renderer.Render(ball, paddleOne, paddleTwo);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(playerOneScore, playerTwoScore, frame_count, paused);
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

  //update paddle positions
  paddleOne.Update(dt);
  paddleTwo.Update(dt);
  
  //update ball positions
  ball.Update(dt);
  
  // Check collisions
  if (Contact contact = CheckPaddleCollision(ball, paddleOne);
		contact.type != CollisionType::None)
	{
		ball.CollideWithPaddle(contact);
	}
	else if (contact = CheckPaddleCollision(ball, paddleTwo);
		contact.type != CollisionType::None)
	{
		ball.CollideWithPaddle(contact);
	}
  	else if (contact = CheckWallCollision(ball);
		contact.type != CollisionType::None)
	{
		ball.CollideWithWall(contact);
      	if (contact.type == CollisionType::Left)
		{
			++playerTwoScore;
          	ResetBoard();
          	paused = true;
		}
		else if (contact.type == CollisionType::Right)
		{
			++playerOneScore;
          	ResetBoard();
          	paused = true;
		}
	}
}

Contact Game::CheckPaddleCollision(Ball const& ball, Paddle const& paddle)
{
	float ballLeft = ball.position.x;
	float ballRight = ball.position.x + 15; //ball width
	float ballTop = ball.position.y;
	float ballBottom = ball.position.y + 15; //ball height

	float paddleLeft = paddle.position.x;
	float paddleRight = paddle.position.x + 5; //paddle width
	float paddleTop = paddle.position.y;
	float paddleBottom = paddle.position.y + 90; //paddle height
  
  	Contact contact{};

	if (ballLeft >= paddleRight)
	{
		return contact;
	}

	if (ballRight <= paddleLeft)
	{
		return contact;
	}

	if (ballTop >= paddleBottom)
	{
		return contact;
	}

	if (ballBottom <= paddleTop)
	{
		return contact;
	}
  
  	float paddleRangeUpper = paddleBottom - (2.0f * 90 / 3.0f);
	float paddleRangeMiddle = paddleBottom - (90 / 3.0f);

	if (ball.velocity.x < 0)
	{
		// Left paddle
		contact.penetration = paddleRight - ballLeft;
	}
	else if (ball.velocity.x > 0)
	{
		// Right paddle
		contact.penetration = paddleLeft - ballRight;
	}

	if ((ballBottom > paddleTop)
	    && (ballBottom < paddleRangeUpper))
	{
		contact.type = CollisionType::Top;
	}
	else if ((ballBottom > paddleRangeUpper)
	     && (ballBottom < paddleRangeMiddle))
	{
		contact.type = CollisionType::Middle;
	}
	else
	{
		contact.type = CollisionType::Bottom;
	}

	return contact;
}

Contact Game::CheckWallCollision(Ball const& ball)
{
	float ballLeft = ball.position.x;
	float ballRight = ball.position.x + 15;
	float ballTop = ball.position.y;
	float ballBottom = ball.position.y + 15;

	Contact contact{};

	if (ballLeft < 0.0f)
	{
		contact.type = CollisionType::Left;
	}
	else if (ballRight > 1280)
	{
		contact.type = CollisionType::Right;
	}
	else if (ballTop < 0.0f)
	{
		contact.type = CollisionType::Top;
		contact.penetration = -ballTop;
	}
	else if (ballBottom > 720)
	{
		contact.type = CollisionType::Bottom;
		contact.penetration = 720 - ballBottom;
	}

	return contact;
}

void Game::ResetBoard() 
{
  paddleOne.position = Vec2(50.0f, (720.0f / 2.0f) - (90.0f / 2.0f));
  paddleTwo.position = Vec2(1280 - 50.0f, (720.0f / 2.0f) - (90.0f / 2.0f));
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
  } else { //this only happens if the game quits early, but it never hurts to be safe
    return "Neither";
  }
}
//int Game::GetSize() const { return snake.size; }