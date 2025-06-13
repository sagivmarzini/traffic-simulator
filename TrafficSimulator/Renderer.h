#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Renderer
{
public:
	Renderer(const sf::VideoMode& videoMode, const std::string& windowName, const int maxFrameRate = 60);

	void drawCircle(sf::Vector2f center, float radius, float borderThickness, sf::Color color);
	void drawRectangle(sf::Vector2f topLeft, float width, float height, float borderThickness, sf::Color color);
	void drawLine(sf::Vector2f a, sf::Vector2f b, float thickness, sf::Color color = sf::Color::White);

	void processEvents();

	bool isOpen() const;
	int getWindowWidth() const;
	int getWindowHeight() const;
	sf::RenderWindow& getWindow();

	void clear(sf::Color color);
	void display();

	enum class Default
	{
		PointRadius = 18,
		LineWidth = 2
	};

private:
	sf::RenderWindow _window;
};