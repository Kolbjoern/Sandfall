#include "GridManager.h"

#include "GridNull.h"

void GridManager::init(int cellSize, int width, int height)
{
	m_currentGrid = new GridNull();
	m_cellSize = cellSize;
	m_width = width;
	m_height = height;
}

void GridManager::changeGrid(IGrid* newGrid)
{
	delete m_currentGrid;
	m_currentGrid = newGrid;
	m_currentGrid->init(m_cellSize, m_width, m_height);
}

void GridManager::setColor(int index, sf::Color color)
{
	m_currentGrid->setColor(index, color);
}

void GridManager::draw(sf::RenderWindow& window)
{
	m_currentGrid->draw(window);
}

unsigned int GridManager::getSize()
{
	return m_currentGrid->getSize();
}

sf::Color GridManager::getColor(int index)
{
	return m_currentGrid->getColor(index);
}