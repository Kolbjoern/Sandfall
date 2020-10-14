#include "Game.h"

#include <SFML/Window/Event.hpp>

#include <cstdlib>

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

const int WORLD_WIDTH = 128;
const int WORLD_HEIGHT = 96;

const int PIXEL_SIZE = 8;

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

	for (int y = 0; y < WORLD_HEIGHT; y++) {
		for (int x = 0; x < WORLD_WIDTH; x++) {
			sf::RectangleShape r;
			r.setPosition(x*(PIXEL_SIZE), y*(PIXEL_SIZE));
			r.setFillColor(sf::Color::Black);
			r.setSize(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));
			m_grid.push_back(r);
		}
	}
	m_currentColor = sf::Color::Yellow;
	m_loopTimer.init();
	m_updateTimer = 0;
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

	int tracker[WORLD_WIDTH * WORLD_HEIGHT] = {};
	for (unsigned int i = 0; i < m_grid.size(); i++) {
		if (m_grid[i].getFillColor() == sf::Color::Yellow) {
			if (tracker[i] & 1) {
				continue;
			}
			processSand(i, tracker);
		}
		else if (m_grid[i].getFillColor() == sf::Color::Blue) {
			if (tracker[i] & 2) {
				continue;
			}
			processWater(i, tracker);
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i p = sf::Mouse::getPosition(m_window);
		int x = p.x / PIXEL_SIZE;
		int y = p.y / PIXEL_SIZE;
		unsigned int index = y * WORLD_WIDTH + x;

		if (index >= 0 && index < m_grid.size()) {
			m_grid[index].setFillColor(m_currentColor);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
		m_currentColor = sf::Color::Yellow;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
		m_currentColor = sf::Color::Blue;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		for (unsigned int i = 0; i < m_grid.size(); i++) {
			m_grid[i].setFillColor(sf::Color::Black);
		}
	}
}

void Game::processSand(int index, int tracker[])
{
	if (changeColor(index, getDown(index), sf::Color::Yellow)) {
		tracker[getDown(index)] |= 1;
	}
	else if (changeColor(index, getDownRight(index), sf::Color::Yellow)) {
		tracker[getDownRight(index)] |= 1;
	}
	else if (changeColor(index, getDownLeft(index), sf::Color::Yellow)) {
		tracker[getDownLeft(index)] |= 1;
	}
}

void Game::processWater(int index, int tracker[])
{
	if (changeColor(index, getDown(index), sf::Color::Blue)) {
		tracker[getDown(index)] |= 2;
	}
	else if (changeColor(index, getDownRight(index), sf::Color::Blue)) {
		tracker[getDownRight(index)] |= 2;
	}
	else if (changeColor(index, getDownLeft(index), sf::Color::Blue)) {
		tracker[getDownLeft(index)] |= 2;
	}
	else if (changeColor(index, getLeft(index), sf::Color::Blue)) {
		tracker[getLeft(index)] |= 2;
	}
	else if (changeColor(index, getRight(index), sf::Color::Blue)) {
		tracker[getRight(index)] |= 2;
	}
}

bool Game::changeColor(unsigned int index, unsigned int target, sf::Color color)
{
	if (isInsideGrid(target) && isAdjacent(index, target)) {
		if (m_grid[target].getFillColor() == sf::Color::Black) {
			m_grid[target].setFillColor(color);
			m_grid[index].setFillColor(sf::Color::Black);
			return true;
		}
	}
	return false;
}

int Game::getLeft(int index)
{
	return index - 1;
}

int Game::getRight(int index)
{
	return index + 1;
}

int Game::getDown(int index)
{
	return index + WORLD_WIDTH;
}

int Game::getDownLeft(int index)
{
	return index + WORLD_WIDTH - 1;
}

int Game::getDownRight(int index)
{
	return index + WORLD_WIDTH + 1;
}

bool Game::isInsideGrid(unsigned int index)
{
	return index < m_grid.size() && index > 0;
}

bool Game::isAdjacent(int index, int target)
{
	return std::abs((index % WORLD_WIDTH) - (target % WORLD_WIDTH)) < 2;
}

void Game::render()
{
	m_window.clear();
	for (unsigned int i = 0; i < m_grid.size(); i++) {
		m_window.draw(m_grid[i]);
	}
	m_window.display();
}