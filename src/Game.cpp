#include "Game.h"

#include <SFML/Window/Event.hpp>

#include <cstdlib>

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

const int PIXEL_SIZE = 4;

const float FPS = 60.0f;

void Game::run()
{
	init();

	while (m_window.isOpen()) {
		m_loopTimer.tick();

		handleInput();
		update(m_loopTimer.getDeltaTime());
		render();
	}
}

void Game::init()
{
	m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sandfall");
	m_window.setFramerateLimit(FPS);

	m_worldWidth = WINDOW_WIDTH / PIXEL_SIZE;
	m_worldHeight = WINDOW_HEIGHT / PIXEL_SIZE;

	for (int y = 0; y < m_worldHeight; y++) {
		for (int x = 0; x < m_worldWidth; x++) {
			sf::RectangleShape r;
			r.setPosition(x*(PIXEL_SIZE), y*(PIXEL_SIZE));
			r.setFillColor(Color::Black);
			r.setSize(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));
			m_grid.push_back(r);
		}
	}
	m_currentColor = Color::Yellow;
	m_loopTimer.init();
	m_updateTimer = 0;
	m_randomGenerator.seed(1337);
}

void Game::handleInput()
{
	sf::Event event;
	while (m_window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed:
				m_window.close();
				break;

			case sf::Event::Resized:
			case sf::Event::LostFocus:
			case sf::Event::GainedFocus:
			case sf::Event::TextEntered:
			case sf::Event::KeyPressed:
			case sf::Event::KeyReleased:
			case sf::Event::MouseWheelMoved:
			case sf::Event::MouseWheelScrolled:
			case sf::Event::MouseButtonPressed:
			case sf::Event::MouseButtonReleased:
			case sf::Event::MouseMoved:
			case sf::Event::MouseEntered:
			case sf::Event::MouseLeft:
			case sf::Event::JoystickButtonPressed:
			case sf::Event::JoystickButtonReleased:
			case sf::Event::JoystickMoved:
			case sf::Event::JoystickConnected:
			case sf::Event::JoystickDisconnected:
			case sf::Event::TouchBegan:
			case sf::Event::TouchMoved:
			case sf::Event::TouchEnded:
			case sf::Event::SensorChanged:
			case sf::Event::Count:
				break;
		}
	}
}

void Game::update(float deltaTime)
{
	m_updateTimer += deltaTime;
	if (m_updateTimer < 0.016f) {
		return;
	}
	m_updateTimer -= 0.016f;

	int tracker[m_worldWidth * m_worldHeight] = {};
	for (unsigned int i = 0; i < m_grid.size(); i++) {
		if (m_grid[i].getFillColor() == Color::Yellow) {
			if (tracker[i] & ParticleType::Sand) {
				continue;
			}
			processSand(i, tracker);
		}
		else if (m_grid[i].getFillColor() == Color::Blue) {
			if (tracker[i] & ParticleType::Water) {
				continue;
			}
			processWater(i, tracker);
		}
		else if (m_grid[i].getFillColor() == Color::Gray) {
			if (tracker[i] & ParticleType::Stone) {
				continue;
			}
			processStone(i, tracker);
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		unsigned int index = getIndexAtMouse();
		if (index >= 0 && index < m_grid.size() && m_grid[index].getFillColor() == Color::Black) {
			setColor(index, m_currentColor);
			setColor(getLeft(index), m_currentColor);
			setColor(getRight(index), m_currentColor);
			setColor(getUp(index), m_currentColor);
			setColor(getUpLeft(index), m_currentColor);
			setColor(getUpRight(index), m_currentColor);
			setColor(getDown(index), m_currentColor);
			setColor(getDownLeft(index), m_currentColor);
			setColor(getDownRight(index), m_currentColor);
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		unsigned int index = getIndexAtMouse();
		if (index >= 0 && index < m_grid.size()) {
			m_grid[index].setFillColor(Color::Black);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
		m_currentColor = Color::Yellow;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
		m_currentColor = Color::Blue;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
		m_currentColor = Color::White;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
		m_currentColor = Color::Gray;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		for (unsigned int i = 0; i < m_grid.size(); i++) {
			m_grid[i].setFillColor(Color::Black);
		}
	}
}

void Game::processSand(int index, int tracker[])
{
	if (process(index, getDown(index), tracker)) {
		tracker[getDown(index)] |= ParticleType::Sand;
	}
	else {
		std::uniform_int_distribution<int> rand(0, 1);
		bool leftFirst = rand(m_randomGenerator) == 0;
		if (leftFirst) {
			if (process(index, getDownLeft(index), tracker)) {
				tracker[getDownLeft(index)] |= ParticleType::Sand;
			}
			else if (process(index, getDownRight(index), tracker)) {
				tracker[getDownRight(index)] |= ParticleType::Sand;
			}
		}
		else {
			if (process(index, getDownRight(index), tracker)) {
				tracker[getDownRight(index)] |= ParticleType::Sand;
			}
			else if (process(index, getDownLeft(index), tracker)) {
				tracker[getDownLeft(index)] |= ParticleType::Sand;
			}
		}
	}
}

void Game::processWater(int index, int tracker[])
{
	if (process(index, getDown(index), tracker)) {
		tracker[getDown(index)] |= ParticleType::Water;
	}
	else {
		std::uniform_int_distribution<int> rand(0, 1);
		bool leftFirst = rand(m_randomGenerator) == 0;
		if (leftFirst) {
			if (process(index, getDownLeft(index), tracker)) {
				tracker[getDownLeft(index)] |= ParticleType::Water;
			}
			else if (process(index, getDownRight(index), tracker)) {
				tracker[getDownRight(index)] |= ParticleType::Water;
			}
			else if (process(index, getLeft(index), tracker)) {
				tracker[getLeft(index)] |= ParticleType::Water;
			}
			else if (process(index, getRight(index), tracker)) {
				tracker[getRight(index)] |= ParticleType::Water;
			}
		}
		else {
			if (process(index, getDownRight(index), tracker)) {
				tracker[getDownRight(index)] |= ParticleType::Water;
			}
			else if (process(index, getDownLeft(index), tracker)) {
				tracker[getDownLeft(index)] |= ParticleType::Water;
			}
			else if (process(index, getRight(index), tracker)) {
				tracker[getRight(index)] |= ParticleType::Water;
			}
			else if (process(index, getLeft(index), tracker)) {
				tracker[getLeft(index)] |= ParticleType::Water;
			}
		}
	}
}

void Game::processStone(int index, int tracker[])
{
	if (process(index, getDown(index), tracker)) {
		tracker[getDown(index)] |= ParticleType::Stone;
	}
}

bool Game::process(unsigned int index, unsigned int target, int tracker[])
{
	if (isInsideGrid(target) && isAdjacent(index, target)) {
		sf::Color color = m_grid[index].getFillColor();
		if (m_grid[target].getFillColor() == Color::Black) {
			m_grid[target].setFillColor(color);
			m_grid[index].setFillColor(Color::Black);
			return true;
		}
		else if ((color == Color::Yellow || color == Color::Gray) 
				&& m_grid[target].getFillColor() == Color::Blue) {
			m_grid[target].setFillColor(color);
			m_grid[index].setFillColor(Color::Blue);
			processWater(index, tracker);
			return true;
		}
	}
	return false;	
}

unsigned int Game::getIndexAtMouse()
{
	sf::Vector2i p = sf::Mouse::getPosition(m_window);
	int x = p.x / PIXEL_SIZE;
	int y = p.y / PIXEL_SIZE;
	unsigned int index = y * m_worldWidth + x;

	return index;
}

void Game::setColor(unsigned int index, sf::Color color)
{
	if (index >= 0 && index < m_grid.size() && m_grid[index].getFillColor() == Color::Black) {
		m_grid[index].setFillColor(color);
	}
}

int Game::getLeft(int index)
{
	return index - 1;
}

int Game::getRight(int index)
{
	return index + 1;
}

int Game::getUp(int index)
{
	return index - m_worldWidth;
}

int Game::getUpLeft(int index)
{
	return index - m_worldWidth - 1;
}

int Game::getUpRight(int index)
{
	return index - m_worldWidth + 1;
}

int Game::getDown(int index)
{
	return index + m_worldWidth;
}

int Game::getDownLeft(int index)
{
	return index + m_worldWidth - 1;
}

int Game::getDownRight(int index)
{
	return index + m_worldWidth + 1;
}

bool Game::isInsideGrid(unsigned int index)
{
	return index < m_grid.size() && index > 0;
}

bool Game::isAdjacent(int index, int target)
{
	return std::abs((index % m_worldWidth) - (target % m_worldWidth)) < 2;
}

void Game::render()
{
	m_window.clear();
	for (unsigned int i = 0; i < m_grid.size(); i++) {
		m_window.draw(m_grid[i]);
	}
	m_window.display();
}