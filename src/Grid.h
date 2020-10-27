#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/rectangleShape.hpp>

#include "common/Color.h"

#include <vector>

class Grid
{
public:
	virtual void init(int cellSize, int width, int height);
};

class GridRectShape : Grid
{
public:
	void init(int cellSize, int width, int height);
	unsigned int getSize();
	void setColor(int index, sf::Color color);
	sf::Color getColor(int index);
	void draw(sf::RenderWindow& window);
private:
	std::vector<sf::RectangleShape> m_grid;
};

struct Cell
{
	sf::Vector2f position;
	sf::Color color;
};

class GridQuad : Grid
{
public:
	void init(int cellSize, int width, int height);
	unsigned int getSize();
	void setColor(int index, sf::Color color);
	sf::Color getColor(int index);
	void draw(sf::RenderWindow& window);
private:
	sf::VertexArray m_grid;
	int m_size;
};