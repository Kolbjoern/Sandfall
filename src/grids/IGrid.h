#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "../common/Color.h"

class IGrid
{
public:
	virtual ~IGrid() = default;
	virtual void init(int cellSize, int width, int height) = 0;
	virtual void setColor(int index, sf::Color color) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual unsigned int getSize() = 0;
	virtual sf::Color getColor(int index) = 0;
};