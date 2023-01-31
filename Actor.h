#pragma once


enum enumObjectsId : uint32_t
{
	Ship = 0,
	Asteroid = 1,
	Bullet = 2
};

struct Actor
{
	Actor() :
		m_x(0.0f), m_y(0.0f),	
		m_rz(0.0f),
		m_vx(0.0f), m_vy(0.0f),
		m_avz(0.0f),
		m_radius(0.0f),
		m_mass(0.0f),
		m_size(0),
		m_actorType(-1),
		m_alive(false)
	{
	}

	float	m_x, m_y;		// position
	float	m_rz;			// orientation (in degrees)
	float	m_vx, m_vy;		// linear velocity
	float	m_avz;			// angular velocity
	float	m_radius;
	float	m_mass;
	int		m_size;			// aka radius index
	int		m_actorType;	//actorType
	bool	m_alive;		// dead or alive
};
