#ifndef PADDLE_H
#define PADDLE_H

#include "SDL.h"
#include "vec2.h"

class Paddle
{
public:
	enum Direction { kUp = 0, kDown }; //used instead of enum class so that it can be used as an array index

	Paddle(Vec2 position, Vec2 velocity);

	SDL_Rect DrawHelper();
    
    void Update(float dt);

	Vec2 position;
    Vec2 velocity;
    bool direction[2] = {};
    bool moving = false;
	SDL_Rect rect{};
};

#endif