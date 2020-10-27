#include "Grid.h"

#include <iostream>

void Grid::init(int cellSize, int width, int height)
{

}

void GridRectShape::init(int cellSize, int width, int height)
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

unsigned int GridRectShape::getSize()
{
	return m_grid.size();
}

void GridRectShape::setColor(int index, sf::Color color)
{
	m_grid[index].setFillColor(color);
}

sf::Color GridRectShape::getColor(int index)
{
	return m_grid[index].getFillColor();
}

void GridRectShape::draw(sf::RenderWindow& window)
{
	for (unsigned int i = 0; i < m_grid.size(); i++) {
		window.draw(m_grid[i]);
	}
}

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

unsigned int GridQuad::getSize()
{
	return m_size;
}

void GridQuad::setColor(int index, sf::Color color)
{
	m_grid[index*4].color = color;
	m_grid[index*4+1].color = color;
	m_grid[index*4+2].color = color;
	m_grid[index*4+3].color = color;
}

sf::Color GridQuad::getColor(int index)
{
	return m_grid[index*4].color;
}

void GridQuad::draw(sf::RenderWindow& window)
{
	window.draw(m_grid);
}