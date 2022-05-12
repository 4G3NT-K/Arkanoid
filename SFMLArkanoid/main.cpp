#include <iostream>
#include <ctime>
#include <string>
#include "functions.h"
#include "figures.h"
#include <sstream>
int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 1024), "Arkanoid");
	window.setFramerateLimit(120);
	Player player;
	sf::Font font;
	const std::string fontName("arial.ttf");
	font.loadFromFile(fontName);

	sf::Text scoreText;
	sf::Text healthText;
	sf::Text lossText;
	scoreText.setFillColor(sf::Color::Yellow);
	scoreText.setFont(font);
	scoreText.setCharacterSize(20);
	scoreText.setPosition(1000, 900);

	healthText.setFillColor(sf::Color::Yellow);
	healthText.setFont(font);
	healthText.setCharacterSize(20);
	healthText.setPosition(1000, 950);

	lossText.setFillColor(sf::Color::Red);
	lossText.setFont(font);
	lossText.setCharacterSize(150);
	lossText.setPosition(windowWidth / 4, windowHeight / 2);
	lossText.setString("YOU DIED");

	Racket rack(windowWidth / 2, windowHeight - 50);
	Ball bl(windowWidth / 2, 3 * windowHeight / 4);



	std::vector <Brick> standardBricks;
	std::vector <Brick> velocityBoostBricks;
	std::vector <Brick> indestructibleBlocks;
	std::vector <Brick> strongerHealthBlocks;
	std::vector <Brick> bonusBlocks;
	std::vector <Bonus> bonuses;
	bonusBlocks.emplace_back(0.85 * windowHeight / 4, windowWidth / 4);
	bonusBlocks.emplace_back(0.55 * windowHeight / 4, 1.3 * windowWidth / 4);
	bonusBlocks[0].setFillColor(sf::Color::Magenta);
	bonusBlocks[1].setFillColor(sf::Color::Magenta);
	bonuses.emplace_back(0.85 * windowHeight / 4, windowWidth / 4);
	bonuses.emplace_back(0.55 * windowHeight / 4, 1.3*windowWidth / 4);


	/*Standard blocks generation*/
	for (int iX = 0; iX < countStandardX; iX++) {
		for (int iY = 0; iY < countStandardY; iY++) {
			standardBricks.emplace_back((iX + 1) * (blockWidth + 3) + 22,
				(iY + 2) * (blockHeight + 3));
		}
	}
	/*Velocity boost blocks*/
	for (int iX = 0; iX < countVelocityBoostBlocks; iX++) {
		velocityBoostBricks.emplace_back(3 * windowWidth / 4, (iX + 2) * (blockHeight + 3));
		velocityBoostBricks[iX].setVelocityBoost(ballVelocityBoost);
		velocityBoostBricks[iX].setFillColor(sf::Color::Green);

	}
	/*Indestructible blocks*/
	for (int iX = 0; iX < countIndestructibleBlocks; iX++) {
		indestructibleBlocks.emplace_back(2 * windowWidth / 6, (iX + 2) * (blockHeight + 3));
		indestructibleBlocks[iX].setDestructibility(false);
		indestructibleBlocks[iX].setFillColor(sf::Color::Red);
		indestructibleBlocks[iX].setHealth(-1);
	}
	/*Stronger health blocks */
	for (int iX = 0; iX < countIndestructibleBlocks; iX++) {
		strongerHealthBlocks.emplace_back(3 * windowWidth / 6, (iX + 2) * (blockHeight + 3));
		strongerHealthBlocks[iX].setFillColor(sf::Color::Cyan);
		strongerHealthBlocks[iX].setHealth(2);
	}


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

		for (auto& brick : standardBricks) {
			testCollision(brick, bl, player);
		}

		for (auto& brick : velocityBoostBricks) {
			testCollision(brick, bl, player);
		}

		for (auto& brick : indestructibleBlocks) {
			testCollision(brick, bl, player);
		}

		for (auto& brick : strongerHealthBlocks) {
			testCollision(brick, bl, player);
		}
		int i = 0;
		for (int i = 0; i < bonusBlocks.size();i++) {
			testCollision(bonusBlocks[i], bl, player);
			if (bonusBlocks[i].getStatus()) {
				bonusBlocks[i].setFillColor(sf::Color::Black);
				bonusBlocks[i].setPosition({ -100,-100 });
				bonuses[i].setMovingStatus(true);
			}
			/*for (auto& bonus : bonuses) {
				if (brick.getStatus()) {
					bonus.setMovingStatus(true);
				}
			}*/

		}

		standardBricks.erase(remove_if(begin(standardBricks), end(standardBricks), [](Brick& brick) {return brick.getStatus(); }), end(standardBricks));
		velocityBoostBricks.erase(remove_if(begin(velocityBoostBricks), end(velocityBoostBricks), [](Brick& brick) {return brick.getStatus(); }), end(velocityBoostBricks));
		indestructibleBlocks.erase(remove_if(begin(indestructibleBlocks), end(indestructibleBlocks), [](Brick& brick) {return brick.getStatus(); }), end(indestructibleBlocks));
		strongerHealthBlocks.erase(remove_if(begin(strongerHealthBlocks), end(strongerHealthBlocks), [](Brick& brick) {return brick.getStatus(); }), end(strongerHealthBlocks));
		std::ostringstream scorestream;
		std::ostringstream healthtream;
		healthtream << player.getHealth();
		scorestream << player.getScore();
		std::string scoretext = "Score: " + scorestream.str();
		scoreText.setString(scoretext);
		healthText.setString("Health: " + healthtream.str());
		
		rack.update();
		bl.update(player);
		testCollision(rack, bl);
		testCollision(rack, bonuses[0]);
		window.clear();
		window.draw(bl);
		window.draw(rack);
		//window.draw(bonuses[0]);
		window.draw(scoreText);
		window.draw(healthText);
		for (auto& brick : standardBricks) {
			window.draw(brick);
		}
		for (auto& brick : velocityBoostBricks) {
			window.draw(brick);
		}
		for (auto& brick : indestructibleBlocks) {
			window.draw(brick);
		}
		for (auto& brick : strongerHealthBlocks) {
			window.draw(brick);
		}
		for (auto& brick : bonusBlocks) {
			window.draw(brick);
		}
		for (auto& bonus : bonuses) {
			if ((!bonus.getStatus())&&(bonus.getMovingStatus())) {
				bonus.update();
			}
			window.draw(bonus);
		}
		for (auto& bonus : bonuses) {
			if (bonus.getStatus()) {
				bonuses.erase(remove_if(begin(bonuses), end(bonuses), [](Bonus& bonus) {return bonus.getStatus(); }), end(bonuses));
			}
		}
		if (player.getHealth() == 0) {
			bl.setVelocity({ 0,0 });
			window.draw(lossText);
		}
		window.display();
	}
	bonusBlocks.erase(remove_if(begin(bonusBlocks), end(bonusBlocks), [](Brick& brick) {return brick.getStatus(); }), end(bonusBlocks));
	return 0;
}