#include "GridQuad.h"

void GridQuad::init(int cellSize, int width, int height)
{
	m_size = height*width;

	m_grid.setPrimitiveType(sf::Quads);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			m_grid.append(sf::Vertex(sf::Vector2f(x*cellSize, y*cellSize), sf::Color::Black));
			m_grid.append(sf::Vertex(sf::Vector2f((x*cellSize)+cellSize, y*cellSize), sf::Color::Black));
			m_grid.append(sf::Vertex(sf::Vector2f((x*cellSize)+cellSize, (y*cellSize)+cellSize), sf::Color::Black));
			m_grid.append(sf::Vertex(sf::Vector2f(x*cellSize, (y*cellSize)+cellSize), sf::Color::Black));
		}
	}
}

void GridQuad::setColor(int index, sf::Color color)
{
	m_grid[index*4].color = color;
	m_grid[index*4+1].color = color;
	m_grid[index*4+2].color = color;
	m_grid[index*4+3].color = color;
}

void GridQuad::draw(sf::RenderWindow& window)
{
	window.draw(m_grid);
}

unsigned int GridQuad::getSize()
{
	return m_size;
}

sf::Color GridQuad::getColor(int index)
{
	return m_grid[index*4].color;
}