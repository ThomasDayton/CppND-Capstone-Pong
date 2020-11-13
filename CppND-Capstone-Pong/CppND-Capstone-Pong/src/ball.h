#ifndef BALL_H
#define BALL_H

#include "SDL.h"
#include "vec2.h"

class Ball
{
public:
	Ball(Vec2 position);

	SDL_Rect DrawHelper();

	Vec2 position;
	SDL_Rect rect{};
};

#endif