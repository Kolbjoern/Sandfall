#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/rectangleShape.hpp>

#include "utils/LoopTimer.h"

class Game
{
public:
	void run();

private:
	void init();
	void handleInput();
	void update(float deltaTime);
	int processSand(int index);
	int processWater(int index);
	bool changeColor(unsigned int index, unsigned int target, sf::Color color);
	bool isInsideGrid(unsigned int index);
	bool isAdjacent(int index, int target);
	void render();

	sf::RenderWindow m_window;
	std::vector<sf::RectangleShape> m_grid;
	sf::Color m_currentColor;

	LoopTimer m_loopTimer;

	float m_updateTimer;
};