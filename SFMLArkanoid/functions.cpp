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

void testCollision(Brick& brick, Ball& ball) {
	if (!isIntersecting(brick, ball)) {
		return;
	}
	brick.setStatus(true);

	float overlapLeft = ball.right() - brick.left();
	float overlapRight = brick.right() - ball.left();
	float overlapTop = ball.bottom() - brick.top();
	float overlapBottom = brick.bottom() - ball.top();

	bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
	bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

	float minOverlapX = ballFromLeft ? overlapLeft : overlapRight;
	float minOverlapY = ballFromTop ? overlapTop : overlapBottom;

	if (abs(minOverlapX) < abs(minOverlapY)) {
		ball.setXVelocity(ballFromLeft ? -ballVelocity : ballVelocity);
	}
	else {
		ball.setYVelocity(ballFromTop ? -ballVelocity : ballVelocity);
	}

}