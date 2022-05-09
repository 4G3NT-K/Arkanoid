#ifndef FIGURES_H
#define FIGURES_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
constexpr float ballRadius{ 20.f }, ballVelocity(8.f); 
constexpr int windowWidth{ 1280 }, windowHeight{ 1024 };
constexpr float racketWidth{ 60.f }, racketHeight{ 20.f }, racketVelocity{ 15.f };
constexpr float blockWidth{ 60.f }, blockHeight{ 20.f };
constexpr float countBlocksX{ 11 }, countBlocksY{ 4 };

class Ball :public sf::CircleShape {
public:
	Ball(float mX, float mY) {
		this->setPosition(mX, mY);
		this->setRadius(ballRadius);
		this->setOrigin(ballRadius, ballRadius);
	}
	void update();
	float x();
	float y();
	float left();
	float right();
	float top();
	float bottom();

	sf::Vector2f getVelocity() { return this->_velocity; }

	void setVelocity(sf::Vector2f velocity) { this->_velocity = velocity; }
	void setXVelocity(float xvelocity) { this->_velocity.x = xvelocity; }
	void setYVelocity(float yvelocity) { this->_velocity.y = yvelocity; }
private:
	sf::Vector2f _velocity{ -ballVelocity, -ballVelocity };
};
class Racket : public sf::RectangleShape {
public:
	Racket(float mX, float mY) {
		this->setPosition(mX, mY);
		this->setSize({ racketWidth, racketHeight });
		this->setOrigin(racketWidth / 2, racketHeight / 2);
	}
	void update();
	float x();
	float y();
	float left();
	float right();
	float top();
	float bottom();

	sf::Vector2f getVelocity() { return this->_velocity; }

	void setVelocity(sf::Vector2f velocity) { this->_velocity = velocity; }
	void setXVelocity(float xvelocity) { this->_velocity.x = xvelocity; }
	void setYVelocity(float yvelocity) { this->_velocity.y = yvelocity; }
private:
	sf::Vector2f _velocity{ -racketVelocity, 0 };
};
class Brick : public sf::RectangleShape {
public:
	Brick(float mX, float mY) {
		this->setPosition(mX, mY);
		this->setSize({ blockWidth, blockHeight });
		this->setFillColor(sf::Color::Yellow);
		this->setOrigin(blockWidth / 2.f, blockHeight / 2.f);
	}
	float x();
	float y();
	float left();
	float right();
	float top();
	float bottom();

	bool getStatus() { return this->_destroyed; }
	void setStatus(bool status) { this->_destroyed = status; }
private:
	bool _destroyed = false;
};
#endif
