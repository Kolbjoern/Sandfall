#pragma once

#include "IGrid.h"

class GridManager
{
	public:
		void init(int cellSize, int width, int height);
		void changeGrid(IGrid* newGrid);
		void setColor(int index, sf::Color color);
		void draw(sf::RenderWindow& window);
		unsigned int getSize();
		sf::Color getColor(int index);

	private:
		IGrid* m_currentGrid;

		int m_cellSize;
		int m_width;
		int m_height;
};