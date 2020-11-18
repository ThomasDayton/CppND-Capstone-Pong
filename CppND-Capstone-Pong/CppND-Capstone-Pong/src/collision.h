#ifndef COLLISION_H
#define COLLISION_H

enum class CollisionType
{
	None,
    Top,
    Middle,
    Bottom,
    Left,
    Right
};

struct Contact
{
  	CollisionType type;
  	float penetration;
};

#endif