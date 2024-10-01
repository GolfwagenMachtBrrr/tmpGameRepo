#pragma once
#include "SFML/Graphics.hpp"
#include "WayPoint.h"
#include "TextureHolder.h"
#include <string>

#include <iostream>

class Enemy
{
public:
	void LoadAssets(TextureHolder &textureholder)
	{
		// access texture Holder 
		// this->m_texture = texture; 
		this->m_bodytexture = textureholder.GetTexture("Skeleton");
	}
	
	void Initialize(const float& speed, const int& damage, const __int32& attackspeed, const WayPoint& waypoint, const sf::Color& color)
	{
		this->m_speed = speed;
		this->m_damage = damage;
		this->m_attackspeed = attackspeed;
		this->m_target = waypoint.target;


		this->m_body.setFillColor(sf::Color::Blue);
		this->m_body.setSize(sf::Vector2f(10, 10));
		this->m_body.setPosition(waypoint.position);

		this->m_position = waypoint.position;

	}

	void Draw(sf::RenderWindow& window) const
	{
		window.draw(m_body);
	}

public:
	// Getter Functions
	sf::Vector2f GetPosition() const
	{
		return this->m_position; 
	}

protected:
	// Movement/shooting Calculations
	sf::Vector2f NormalizeVector(sf::Vector2f& input) const
	{
		float m = sqrt(input.x * input.x + input.y * input.y);
		sf::Vector2f normalizedVector;

		normalizedVector.x = input.x /= m;
		normalizedVector.y = input.y /= m;

		return normalizedVector;
	}

	sf::Vector2f GetDirectionVector() const
	{
		sf::Vector2f direction;
		direction = m_target - m_position;
		direction = NormalizeVector(direction);

		return direction;
	}

	sf::Vector2f GetDirectionVector(const sf::Vector2f& target) const
	{
		sf::Vector2f direction;
		direction = target - m_position;
		direction = NormalizeVector(direction);

		return direction;
	}

	sf::Vector2f GetClosestTarget(const sf::Vector2f& firstTarget, const sf::Vector2f& secondTarget) const
	{
		float diff_first = std::abs(firstTarget.x - this->m_position.x);
		diff_first += std::abs(firstTarget.y - this->m_position.y);

		float diff_second = std::abs(secondTarget.x - this->m_position.x);
		diff_second += std::abs(secondTarget.y - this->m_position.y);

		if (diff_first < diff_second)
		{
			return this->GetDirectionVector(firstTarget);
		}

		return this->GetDirectionVector(secondTarget);
	}
protected:

	int DamageDealtToEnemy(const sf::FloatRect& object_in_danger_of_collison_with_the_wild_enemy) const
	{
		if (object_in_danger_of_collison_with_the_wild_enemy.contains(m_body.getPosition()))
		{
			return this->m_damage;
		}

		return NULL;
	}

	bool AttackTimeoutPassed()
	{
		float timePassedSinceLastRestart = this->m_attacktimer.getElapsedTime().asMilliseconds();
		if (timePassedSinceLastRestart > this->m_attackspeed)
		{
			this->m_attacktimer.restart();
			return true;
		}
		this->m_attacktimer.restart();
		return false;
	}

	bool TargetReached()
	{
		if (this->m_position == this->m_target)
		{
			return true;
		}

		if (this->m_health <= 0)
		{
			return true;
		}

		return false;
	}

public: 
	int p_deflectionRadius; 
private:
	sf::Texture m_bodytexture;
	sf::Sprite  m_bodysprite; 

protected:

	float   m_speed;
	float	m_range; //@Lukas Bawaronschütz
	int     m_damage;
	int		m_health;

	sf::Clock m_attacktimer;
	__int32 m_attackspeed;

	// obviously not a red 10by10 cube 
	sf::RectangleShape m_body;

	sf::Vector2f m_position;
	sf::Vector2f m_target;
};