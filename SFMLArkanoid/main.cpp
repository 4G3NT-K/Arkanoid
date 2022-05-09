
#include <ctime>
#include "functions.h"
#include "figures.h"
int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 1024), "Arkanoid");
	window.setFramerateLimit(60);
	Racket rack(windowWidth / 2, windowHeight - 50);
	Ball bl(windowWidth / 2, windowHeight / 2);
	std::vector <Brick> bricks;

	for (int iX = 0; iX < countBlocksX; iX++) {
		for (int iY = 0; iY < countBlocksY; iY++) {
			bricks.emplace_back((iX + 1) * (blockWidth + 3) + 22,
				(iY + 2) * (blockHeight + 3));
		}
	}

	Brick brick(windowWidth / 2, windowHeight / 2);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
		}
		window.clear();

		
		for (auto& brick : bricks) {
			testCollision(brick, bl);
		}

		bricks.erase(remove_if(begin(bricks), end(bricks), [](Brick& brick) {return brick.getStatus(); }), end(bricks));

		rack.update();
		bl.update();
		testCollision(rack, bl);

		window.draw(bl);
		window.draw(rack);
		for (auto& brick : bricks) {
			window.draw(brick);
		}
		window.display();
	}

	return 0;
}