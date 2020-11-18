#include <iostream>
#include "ball.h"

Ball::Ball(Vec2 position, Vec2 velocity)
		: position(position), velocity(velocity)
	{
		rect.x = static_cast<int>(position.x);
		rect.y = static_cast<int>(position.y);
		rect.w = 15;
		rect.h = 15;
	}

void Ball::Update(float dt)
	{
  		//std::cout << position.x << " " << velocity.x << std::endl; //for debug
  		position += velocity * dt;
	}

SDL_Rect Ball::DrawHelper()
	{
		rect.x = static_cast<int>(position.x);
		rect.y = static_cast<int>(position.y);

		return rect;
  		//SDL_RenderFillRect(renderer, &rect);
	}

void Ball::CollideWithPaddle(Contact const& contact)
	{
		position.x += contact.penetration;
		velocity.x = -velocity.x;

		if (contact.type == CollisionType::Top)
		{
			velocity.y = -.75f * 1.0f;
		}
		else if (contact.type == CollisionType::Bottom)
		{
			velocity.y = 0.75f * 1.0f;
		}
	}

void Ball::CollideWithWall(Contact const& contact)
	{
		if ((contact.type == CollisionType::Top)
		    || (contact.type == CollisionType::Bottom))
		{
			position.y += contact.penetration;
			velocity.y = -velocity.y;
		}
		else if (contact.type == CollisionType::Left)
		{
			position.x = 1280 / 2.0f;
			position.y = 720 / 2.0f;
			velocity.x = 1.0f;
			velocity.y = 0.0f;
		}
		else if (contact.type == CollisionType::Right)
		{
			position.x = 1280 / 2.0f;
			position.y = 720 / 2.0f;
			velocity.x = -1.0f;
			velocity.y = 0.0f;
		}
	}