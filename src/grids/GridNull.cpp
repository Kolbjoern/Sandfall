#include "GridNull.h"

void GridNull::init(int cellSize, int width, int height) {}
void GridNull::setColor(int index, sf::Color color) {}
void GridNull::draw(sf::RenderWindow& window) {}

unsigned int GridNull::getSize()
{
	return 0;
}

sf::Color GridNull::getColor(int index)
{
	return Color::Black;
}