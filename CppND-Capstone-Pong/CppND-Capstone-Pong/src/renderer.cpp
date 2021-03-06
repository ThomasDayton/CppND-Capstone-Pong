#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Ball &ball, Paddle &paddleOne, Paddle &paddleTwo) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);
  
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  
  //render net
  for (int y = 0; y < screen_height; y++)
  {
    if (y % 5)
    {
      SDL_RenderDrawPoint(sdl_renderer, screen_width/2, y);
    }
  }
  
  // Render Ball
  block = ball.DrawHelper();
  SDL_RenderFillRect(sdl_renderer, &block);
  
  // Render Paddles
  block = paddleOne.DrawHelper();
  SDL_RenderFillRect(sdl_renderer, &block);
  
  block = paddleTwo.DrawHelper();
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int p1score, int p2score, int fps, bool paused) {
  
  std::string title;
  if (paused)
  {
    title = "Pong (Press Enter) P1 Score: " + std::to_string(p1score) + " P2 Score: " + std::to_string(p2score) + " FPS: " + std::to_string(fps);
  } else {
  	title = "Pong P1 Score: " + std::to_string(p1score) + " P2 Score: " + std::to_string(p2score) + " FPS: " + std::to_string(fps);
  }
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
