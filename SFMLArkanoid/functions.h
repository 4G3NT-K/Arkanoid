#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "figures.h"
template <class T1, class T2> bool isIntersecting(T1& A, T2& B);
void testCollision(Racket& racket, Ball& ball);
void testCollision(Brick& brick, Ball& ball, Player& player);
void testCollision(Racket& racket, Bonus& bonus);
#endif 

