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
	void render();

	sf::RenderWindow m_window;
	std::vector<sf::RectangleShape> m_grid;

	LoopTimer m_loopTimer;

	float m_updateTimer;
};