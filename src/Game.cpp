#include "Game.h"

#include <SFML/Window/Event.hpp>

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

	int sand[WORLD_WIDTH * WORLD_HEIGHT] = {0};
	for (unsigned int i = 0; i < m_grid.size(); i++) {
		if (m_grid[i].getFillColor() == sf::Color::Yellow) {
			if (sand[i] == 1) {
				continue;
			}

			unsigned int below = i + WORLD_WIDTH;
			if (below < m_grid.size() && m_grid[below].getFillColor() == sf::Color::Black) {
				m_grid[below].setFillColor(sf::Color::Yellow);
				m_grid[i].setFillColor(sf::Color::Black);
				sand[below] = 1;
			}
			else if (below+1 < m_grid.size() && m_grid[below+1].getFillColor() == sf::Color::Black) {
				m_grid[below+1].setFillColor(sf::Color::Yellow);
				m_grid[i].setFillColor(sf::Color::Black);
				sand[below+1] = 1;
			}
			else if (below-1 < m_grid.size() && m_grid[below-1].getFillColor() == sf::Color::Black) {
				m_grid[below-1].setFillColor(sf::Color::Yellow);
				m_grid[i].setFillColor(sf::Color::Black);
				sand[below-1] = 1;
			}
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i p = sf::Mouse::getPosition(m_window);
		int x = p.x / PIXEL_SIZE;
		int y = p.y / PIXEL_SIZE;
		unsigned int index = y * WORLD_WIDTH + x;

		if (index >= 0 && index < m_grid.size()) {
			m_grid[index].setFillColor(sf::Color::Yellow);
			m_grid[index+1].setFillColor(sf::Color::Yellow);
			m_grid[index-1].setFillColor(sf::Color::Yellow);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		for (unsigned int i = 0; i < m_grid.size(); i++) {
			m_grid[i].setFillColor(sf::Color::Black);
		}
	}
}

void Game::render()
{
	m_window.clear();
	for (unsigned int i = 0; i < m_grid.size(); i++) {
		m_window.draw(m_grid[i]);
	}
	m_window.display();
}