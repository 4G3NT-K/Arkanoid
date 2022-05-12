#include "figures.h"
#include "functions.h"

template <class T1, class T2> bool isIntersecting(T1& A, T2&  B) {
	return (A.right() >= B.left()) && (A.left() <= B.right()) && (A.bottom() >= B.top()) && (A.top() <= B.bottom());
} 

void testCollision(Racket& racket, Ball& ball) {
	if (!isIntersecting(racket, ball)) {
		return;
	}
	ball.setYVelocity(-ballVelocity);
	if (ball.x() < racket.x()) {
		ball.setXVelocity(-ballVelocity);
	}
	else {
		ball.setXVelocity(ballVelocity);
	}
}

void testCollision(Brick& brick, Ball& ball, Player& player) {
	if (!isIntersecting(brick, ball)) {
		return;
	} 
	if (brick.getHealth() > 0) {
		player.scoreIncrease();
		brick.healthDecrease();
	}
	/*We delete only destructible blocks. Setting status "destroyed" to delete later*/
	if (brick.getDestructibility() && (brick.getHealth() == 0)) {
		brick.setStatus(true);
	}
	/*Speed boost*/
	if (brick.getVelocityBoost() == 1.f) {
		ball.setVelocity({ (ball.getVelocity().x > 0) ? ballVelocity : -ballVelocity,(ball.getVelocity().y > 0) ? ballVelocity : -ballVelocity });
	}
	else ball.setVelocity({ ball.getVelocity().x * brick.getVelocityBoost(), ball.getVelocity().y * brick.getVelocityBoost() });



	float overlapLeft = ball.right() - brick.left();
	float overlapRight = brick.right() - ball.left();
	float overlapTop = ball.bottom() - brick.top();
	float overlapBottom = brick.bottom() - ball.top();

	bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
	bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

	float minOverlapX = ballFromLeft ? overlapLeft : overlapRight;
	float minOverlapY = ballFromTop ? overlapTop : overlapBottom;

	if (abs(minOverlapX) < abs(minOverlapY)) {
		ball.setXVelocity(ballFromLeft ? -abs(ball.getVelocity().x) : abs(ball.getVelocity().x));
	}
	else {
		ball.setYVelocity(ballFromTop ? -abs(ball.getVelocity().y) : abs(ball.getVelocity().y));
	}

}

void testCollision(Racket& racket, Bonus& bonus) {
	if (!isIntersecting(racket, bonus)) {
		return;
	}
	else {
		bonus.setStatus(true);
	}
}