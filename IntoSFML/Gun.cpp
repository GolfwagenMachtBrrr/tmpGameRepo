#include "Gun.h"
#include <iostream>
// https://www.youtube.com/watch?v=k6VIez6pnbc
// https://gamefromscratch.com/sfml-with-c-tutorial-series-windows-game-loops-and-timers/
// https://www.youtube.com/watch?v=HccMBtyXwFo

sf::Vector2f Normalize(sf::Vector2f a)
{
	float m = sqrt(a.x * a.x + a.y * a.y);
	sf::Vector2f normalizedVector;

	normalizedVector.x = a.x /= m;
	normalizedVector.y = a.y /= m;

	return normalizedVector;
}


bool AABB(sf::FloatRect a, sf::FloatRect b)
{
	if (a.left + a.width > b.left &&
		b.left + b.width > a.left &&
		b.top + b.height > a.top &&
		a.top + a.height > b.top)
	{
		return true;
	}
	return false;
}

void Gun::Update(const float &dt, const sf::Vector2f &player_position, const sf::Vector2f& mouse_position,
				 std::vector<Spawner> & spawners)
{

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		
		if (this->GetAttackTimer())
		{
			Bullet bullet(10, 0.5);
			bullet.body.setSize(sf::Vector2f(5, 2.5));
			bullet.body.setPosition(player_position);
			m_bullets.push_back(bullet);

			CreateBulletTarget(m_bullets.size() - 1, mouse_position);
		}
			
	}

	for (int i = 0; i < m_bullets.size(); i++)
	{
		sf::Vector2f bulletDirection = m_bullets[i].target.getPosition() - m_bullets[i].body.getPosition();
		bulletDirection = Normalize(bulletDirection);

		m_bullets[i].body.setPosition(m_bullets[i].body.getPosition() + bulletDirection * m_bullets[i].speed);
	}


	for (size_t i = 0; i < m_bullets.size(); i++)
	{
		// Spawner
		bool CollisionDetected = false; 
		for (auto& spawner : spawners)
		{
			if (!CollisionDetected) {

				if (AABB(m_bullets[i].body.getGlobalBounds(), spawner.p_hitbox.getGlobalBounds())) {
					CollisionDetected = true;
					spawner.p_health -= m_bullets[i].damage;
					m_bullets.erase(m_bullets.begin() + i);
					break;
				}
				if (spawner.CheckNPCCollisions(m_bullets[i].body.getGlobalBounds(), m_bullets[i].damage)) {
					CollisionDetected = true;
					m_bullets.erase(m_bullets.begin() + i);
					break;
				}
			}
			
		}
		if (!CollisionDetected) {
			if (AABB(m_bullets[i].body.getGlobalBounds(), m_bullets[i].target.getGlobalBounds())) {
				m_bullets.erase(m_bullets.begin() + i);
			}
		}
		
		
	}

}

void Gun::CreateBulletTarget(const int& index, const sf::Vector2f& mousePos)
{
	sf::RectangleShape boundingRect;
	boundingRect.setSize(sf::Vector2f(20, 20));
	boundingRect.setFillColor(sf::Color::Transparent);
	boundingRect.setOutlineColor(sf::Color::Blue);
	boundingRect.setOutlineThickness(1);
	boundingRect.setPosition(sf::Vector2f(mousePos.x, mousePos.y));
	this->m_bullets[index].target = boundingRect;
}

const bool Gun::GetAttackTimer()
{
	if (this->m_attacktimer.getElapsedTime().asMilliseconds() >= this->m_attacktimermax)
	{
		this->m_attacktimer.restart();
		return true; 
	}
	return false;
}

void Gun::Draw(sf::RenderWindow& window)
{
	for (const auto& bullet : m_bullets) { window.draw(bullet.body); }
	for (const auto& bullet : m_bullets) { window.draw(bullet.target); }
}
