#ifndef BALL_H
#define BALL_H


#include "collision.h"
#include "SDL.h"
#include "vec2.h"

class Ball
{
public:

	Ball(Vec2 position, Vec2 veloctity);

	void Update(float dt);
	SDL_Rect DrawHelper();
    void CollideWithPaddle(Contact const& contact);
    void CollideWithWall(Contact const& contact);

	Vec2 position;
    Vec2 velocity;
	SDL_Rect rect{};
};

#endif