#include "Renderer.h"

#include <numbers>

Renderer::Renderer(const sf::VideoMode& videoMode, const std::string& windowName, const int maxFrameRate)
	: _window(videoMode, windowName)
{
	_window.setFramerateLimit(maxFrameRate);
}

void Renderer::drawCircle(sf::Vector2f center, float radius, float outlineThickness, sf::Color color, sf::Color outlineColor)
{
	sf::CircleShape circle(radius);
	circle.setOrigin({ radius, radius });
	circle.setPosition({ center.x, center.y });
	circle.setOutlineColor(outlineColor);
	circle.setOutlineThickness(outlineThickness);
	circle.setFillColor(color);
	_window.draw(circle);
}

void Renderer::drawRectangle(sf::Vector2f topLeft, float width, float height, float borderThickness, sf::Color color, float rotation)
{
	sf::RectangleShape shape({ width - 2 * borderThickness, height - 2 * borderThickness });
	shape.setPosition({ topLeft.x + borderThickness, topLeft.y + borderThickness });
	shape.setFillColor(color);
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(borderThickness);

	if (rotation != 0.0f) {
		// Set origin to center for proper rotation
		shape.setOrigin({ (width - 2 * borderThickness) / 2.0f, (height - 2 * borderThickness) / 2.0f });
		// Adjust position to account for origin change
		shape.setPosition({ topLeft.x + width / 2.0f, topLeft.y + height / 2.0f });
		shape.setRotation(sf::degrees(rotation));
	}

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

void Renderer::drawDashedLine(sf::Vector2f a, sf::Vector2f b, float thickness, sf::Color color, float dashLength, float gapLength)
{
	sf::Vector2f direction = b - a;
	float totalLength = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (totalLength == 0.0f) return;

	// Normalize direction vector
	direction /= totalLength;

	float currentPos = 0.0f;
	bool drawDash = true;

	while (currentPos < totalLength) {
		float segmentLength = drawDash ? dashLength : gapLength;

		// Don't exceed the total line length
		if (currentPos + segmentLength > totalLength) {
			segmentLength = totalLength - currentPos;
		}

		if (drawDash) {
			sf::Vector2f segmentStart = a + direction * currentPos;
			sf::Vector2f segmentEnd = a + direction * (currentPos + segmentLength);

			// Create rectangle for dash segment
			sf::RectangleShape dash;
			dash.setSize({ segmentLength, thickness });
			dash.setPosition(segmentStart);
			dash.setFillColor(color);

			// Calculate rotation angle
			float angle = std::atan2(direction.y, direction.x) * 180.0f / std::numbers::pi_v<float>;
			dash.setRotation(sf::degrees(angle));

			// Adjust position to center the thickness
			sf::Vector2f perpendicular(-direction.y, direction.x);
			dash.setPosition(segmentStart - perpendicular * (thickness / 2.0f));

			_window.draw(dash);
		}

		currentPos += segmentLength;
		drawDash = !drawDash;
	}
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