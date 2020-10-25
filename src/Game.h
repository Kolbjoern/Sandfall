#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/rectangleShape.hpp>

#include "utils/LoopTimer.h"
#include "common/Color.h"

enum ParticleType : int
{
	Void = 0,
	Sand = 1,
	Water = 2,
	Wall = 4,
	Stone = 8
};

class Game
{
public:
	void run();

private:
	void init();
	void handleInput();
	void update(float deltaTime);
	void processSand(int index, int tracker[]);
	void processWater(int index, int tracker[]);
	void processStone(int index, int tracker[]);
	bool process(unsigned int index, unsigned int target, int tracker[]);
	int getLeft(int index);
	int getRight(int index);
	int getDown(int index);
	int getDownLeft(int index);
	int getDownRight(int index);
	bool isInsideGrid(unsigned int index);
	bool isAdjacent(int index, int target);
	void render();

	sf::RenderWindow m_window;
	std::vector<sf::RectangleShape> m_grid;
	sf::Color m_currentColor;

	LoopTimer m_loopTimer;

	float m_updateTimer;
};