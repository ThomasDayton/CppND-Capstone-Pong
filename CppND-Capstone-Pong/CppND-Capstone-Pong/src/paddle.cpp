#include "paddle.h"

Paddle::Paddle(Vec2 position, Vec2 velocity)
		: position(position), velocity(velocity)
	{
		rect.x = static_cast<int>(position.x);
		rect.y = static_cast<int>(position.y);
		rect.w = 5;
		rect.h = 90;
	}

SDL_Rect Paddle::DrawHelper()
	{
		rect.x = static_cast<int>(position.x);
		rect.y = static_cast<int>(position.y);

		return rect;
  		//SDL_RenderFillRect(renderer, &rect);
	}
void Paddle::Update(float dt)
	{
  		if (moving)
        {
          	if (direction[Direction::kUp])
            {
              	velocity.y = -0.5f;
            } else if (direction[Direction::kDown])
            {
              	velocity.y = 0.5f;
            }
        } else {
          	velocity.y = 0.0f;
        }
  
  		position += velocity * dt;
  		if (position.y < 0)
		{
			// Restrict to top of the screen
			position.y = 0;
		}
  		else if (position.y > 630) //window height - paddle height
        {
          	position.y = 630;
        }
	}