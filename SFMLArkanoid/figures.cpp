#include "figures.h"

float Ball::x() { return this->getPosition().x; }
float Ball::y() { return this->getPosition().y; }
float Ball::left() { return x() - this->getRadius(); }
float Ball::right() { return x() + this->getRadius(); }
float Ball::top() { return y() - this->getRadius(); }
float Ball::bottom() { return y() + this->getRadius(); }
void Ball::update() {
	this->move(_velocity);
	if (left() < 0) {
		_velocity.x = ballVelocity;
	}
	else if (right() > windowWidth) {
		_velocity.x = -ballVelocity;
	}
	if (top() < 0) {
		_velocity.y = ballVelocity;
	}
	else if (bottom() > windowHeight) {
		_velocity.y = -ballVelocity;
	}

}

float Racket::x() { return this->getPosition().x; }
float Racket::y() { return this->getPosition().y; }
float Racket::left() { return x() - this->getSize().x / 2.f; }
float Racket::right() { return x() + this->getSize().x / 2.f; }
float Racket::top() { return y() - this->getSize().y / 2.f; }
float Racket::bottom() { return y() + this->getSize().y / 2.f; }

void Racket::update() {
	this->move(_velocity);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && left() > 0) {
		setXVelocity(-racketVelocity);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && right() < windowWidth) {
		setXVelocity(racketVelocity);
	}
	else {
		setXVelocity(0);
	}
}

float Brick::x() { return this->getPosition().x; }
float Brick::y() { return this->getPosition().y; }
float Brick::left() { return x() - this->getSize().x / 2.f; }
float Brick::right() { return x() + this->getSize().x / 2.f; }
float Brick::top() { return y() - this->getSize().y / 2.f; }
float Brick::bottom() { return y() + this->getSize().y / 2.f; }