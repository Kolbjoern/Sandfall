#pragma once

#include "IGrid.h"

#include <SFML/Graphics/rectangleShape.hpp>

#include <vector>

class GridRect : public IGrid
{
	virtual void init(int cellSize, int width, int height) override;
	virtual void setColor(int index, sf::Color color) override;
	virtual void draw(sf::RenderWindow& window) override;
	virtual unsigned int getSize() override;
	virtual sf::Color getColor(int index) override;

private:
	std::vector<sf::RectangleShape> m_grid;
};