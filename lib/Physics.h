#pragma once
#include "../Actor.h"
#include <cmath>

struct Bounds
{
	//Default constructor
	Bounds(): x(0.0f), y(0.0f), width(0.0f), height(0.0f){}

	//Specialized constructor
	Bounds(float mx, float my, float mwidhth, float mheight):
		x(mx), y(my), width(mwidhth), height(mheight)
	{
	}

	float x;
	float y;
	float width;
	float height;
};

inline bool BoundingBoxCollision(const Actor& player, const Actor& asteroid)
{
	if (player.m_x < asteroid.m_x + asteroid.m_size &&
		player.m_x + player.m_size > asteroid.m_size &&
		player.m_y < asteroid.m_y + asteroid.m_size &&
		player.m_y + player.m_size > asteroid.m_size)
	{
		return true;
	}
	return false;
}

inline bool SphereCollision(const Actor& player, const Actor& asteroid)
{
	int dx = player.m_x - asteroid.m_x;
	int dy = player.m_y - asteroid.m_y;
	int distance = sqrt(dx*dx + dy * dy);

	if (distance < player.m_radius + asteroid.m_radius)
	{
		return true;
	}
	return false;
}