#include "Renderer.h"

Renderer::Renderer(const sf::VideoMode& videoMode, const std::string& windowName, const int maxFrameRate)
	: _window(videoMode, windowName)
{
	_window.setFramerateLimit(maxFrameRate);
}

void Renderer::drawCircle(sf::Vector2f center, float radius, float borderThickness = 0, sf::Color color = sf::Color::White)
{
	sf::CircleShape circle(radius);
	circle.setOrigin({ radius, radius });
	circle.setPosition({ center.x, center.y });
	circle.setOutlineColor(sf::Color::White);
	circle.setOutlineThickness(borderThickness);
	circle.setFillColor(color);
	_window.draw(circle);
}

void Renderer::drawRectangle(sf::Vector2f topLeft, float width, float height, float borderThickness = 0, sf::Color color = sf::Color::White)
{
	sf::RectangleShape shape({ width - 2 * borderThickness, height - 2 * borderThickness });
	shape.setPosition({ topLeft.x + borderThickness, topLeft.y + borderThickness });
	shape.setFillColor(color);
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(borderThickness);
	_window.draw(shape);
}

void Renderer::drawLine(sf::Vector2f a, sf::Vector2f b, float thickness, sf::Color color)
{
	sf::Vector2f direction = b - a;
	float length = direction.length();

	sf::RectangleShape line({ length, thickness });
	line.setPosition(a);
	line.setFillColor(color);

	// Convert angle to sf::Angle using sf::radians
	sf::Angle angle = sf::radians(std::atan2(direction.y, direction.x));
	line.setRotation(angle);

	// Move to center it around the line (optional)
	line.setOrigin({ 0, thickness / 2.f });

	_window.draw(line);
}

bool Renderer::isOpen() const
{
	return _window.isOpen();
}

int Renderer::getWindowWidth() const
{
	return _window.getSize().x;
}

int Renderer::getWindowHeight() const
{
	return _window.getSize().y;
}

sf::RenderWindow& Renderer::getWindow()
{
	return _window;
}

void Renderer::clear(sf::Color color)
{
	_window.clear(color);
}

void Renderer::display()
{
	_window.display();
}