#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Renderer
{
public:
	Renderer(const sf::VideoMode& videoMode, const std::string& windowName, const int maxFrameRate = 60);

	void drawCircle(sf::Vector2f center, float radius, float outlineThickness, sf::Color color = sf::Color::White, sf::Color outlineColor = sf::Color::White);
	void drawRectangle(sf::Vector2f topLeft, float width, float height, float borderThickness, sf::Color color, float rotation = 0.0f);
	void drawLine(sf::Vector2f a, sf::Vector2f b, float thickness, sf::Color color = sf::Color::White);
	void drawDashedLine(sf::Vector2f a, sf::Vector2f b, float thickness, sf::Color color = sf::Color::White, float dashLength = 10.0f, float gapLength = 5.0f);

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