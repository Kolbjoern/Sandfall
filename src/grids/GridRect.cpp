#include "GridRect.h"

void GridRect::init(int cellSize, int width, int height)
{
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			sf::RectangleShape r;
			r.setPosition(x*cellSize, y*cellSize);
			r.setFillColor(Color::Black);
			r.setSize(sf::Vector2f(cellSize, cellSize));
			m_grid.push_back(r);
		}
	}
}

unsigned int GridRect::getSize()
{
	return m_grid.size();
}

void GridRect::setColor(int index, sf::Color color)
{
	m_grid[index].setFillColor(color);
}

sf::Color GridRect::getColor(int index)
{
	return m_grid[index].getFillColor();
}

void GridRect::draw(sf::RenderWindow& window)
{
	for (unsigned int i = 0; i < m_grid.size(); i++) {
		window.draw(m_grid[i]);
	}
}