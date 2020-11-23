#pragma once

#include "IGrid.h"

class GridNull : public IGrid
{
public:
	virtual void init(int cellSize, int width, int height) override;
	virtual void setColor(int index, sf::Color color) override;
	virtual void draw(sf::RenderWindow& window) override;
	virtual unsigned int getSize() override;
	virtual sf::Color getColor(int index) override;	
};