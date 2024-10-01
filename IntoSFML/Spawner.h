#pragma once
#include "SFML/Graphics.hpp"
#include "TextureHolder.h"
#include "Enemy_high.h"


#include <random>
#include <vector>
#include <iostream>

 // https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/ -> random number between upper&lower bound


class Spawner
{
public:

	enum SpawnType
	{
		ZOMBIE,
		SKELETON,
		BANDIT
	};


public:
	void Initialize(const TextureHolder& textureholder);
	void Update(const int &deltatime, const sf::Vector2f &player_position)
	{
		this->u_deltatime = deltatime; 
		this->u_playerposition = player_position; 

		if (this->TimePassed() && this->m_isActive)
		{
			this->SpawnNPC(player_position);
		}

		
	}
	void Draw(sf::RenderWindow& window)
	{
		for (auto enemy : m_enemies)
		{
			enemy.Draw(window);
		}
	}
private: 

	void Kill(); 
	void SpawnNPC(const sf::Vector2f &player_position)
	{
		WayPoint wp;
		wp.position = CalculatePosition();
		wp.target = player_position;
		Enemy enemy;

		switch (p_type)
		{
		case Spawner::ZOMBIE:
			enemy.Initialize(5, 10, 100, wp, sf::Color::White); //stats sollen aus zombie.txt gelesen werden
			enemy.LoadAssets(m_textureholder);
			break;
		case Spawner::SKELETON:
			break;
		case Spawner::BANDIT:
			break;
		default:
			break;
		}
	}
	void KillNPC(const int &NPC_index);
	void KillAllNPCs();

	sf::Vector2f CalculatePosition() 
	{ 
		sf::Vector2f nPosition; 
		int nPosX, nPosY; 

		do
		{
			int ubX = this->m_position.x + this->m_spawnradius, lbX = this->m_position.x - this->m_spawnradius;
			int ubY = this->m_position.y + this->m_spawnradius, lbY = this->m_position.y - this->m_spawnradius;

			nPosX = (rand() % (ubX - lbX + 1)) + lbX;
			nPosY = (rand() % (ubY - lbY + 1)) + lbY;

			nPosition.x = nPosX; 
			nPosition.y = nPosY;
		} while (IsOverlapping(nPosition));
		
		return nPosition;
	}

	bool TimePassed()
	{
		int timeellapsed = this->m_clock.getElapsedTime().asMilliseconds();
		if (timeellapsed >= this->m_spawnrate)
		{
			this->m_clock.restart();
			return true;
		}

		return false; 
	}

	bool IsOverlapping(const sf::Vector2f &position)
	{
		for (auto enemy : m_enemies)
		{
			if (position.x > enemy.GetPosition().x + enemy.p_deflectionRadius,
				position.x < enemy.GetPosition().x - enemy.p_deflectionRadius,
				position.y > enemy.GetPosition().y + enemy.p_deflectionRadius,
				position.y < enemy.GetPosition().y - enemy.p_deflectionRadius)
			{
				return false; 
			}
		}
		return true; 
	}

private:
	// Utillity
	sf::Vector2f u_playerposition;
	int		     u_deltatime; 

	int		m_spawnradius; // not entire radius
	int		m_capacity; 
	int		m_enemycount; 
	int		m_healt; 
	__int32 m_spawnrate = 500; 

	bool m_isActive;

	sf::Texture m_texture; 
	sf::Sprite m_sprite; 

	sf::Clock m_clock;
	sf::Vector2f m_position; 

private:
	std::vector<Enemy_High> m_enemies; 
	TextureHolder           m_textureholder; 
	
public:

	SpawnType p_type; 
};

