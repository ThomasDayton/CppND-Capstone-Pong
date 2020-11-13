#include "ball.h"

Ball::Ball(Vec2 position)
		: position(position)
	{
		rect.x = static_cast<int>(position.x);
		rect.y = static_cast<int>(position.y);
		rect.w = 15;
		rect.h = 15;
	}

SDL_Rect Ball::DrawHelper()
	{
		rect.x = static_cast<int>(position.x);
		rect.y = static_cast<int>(position.y);

		return rect;
  		//SDL_RenderFillRect(renderer, &rect);
	}