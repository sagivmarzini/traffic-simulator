#include "Point.h"

Point::Point(const sf::Vector2f& vector)
	: sf::Vector2f(vector)
{
}

void Point::draw(Renderer& renderer) const
{
	renderer.drawCircle(*this, (int)Renderer::Default::PointRadius, 0, sf::Color::White);
}

void Point::drawWithOutline(Renderer& renderer, float width, const sf::Color& outlineColor) const
{
	renderer.drawCircle(*this, (int)Renderer::Default::PointRadius, width, sf::Color::White, outlineColor);
}