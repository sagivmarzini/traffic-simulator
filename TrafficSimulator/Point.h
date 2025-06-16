#pragma once
#include <SFML/Graphics.hpp>
#include "Renderer.h"

class Point : public sf::Vector2f
{
public:
	using sf::Vector2f::Vector2f; // inherit constructors
	Point(const sf::Vector2f& vector);

	void draw(Renderer& renderer) const;
	void drawWithOutline(Renderer& renderer, float width, const sf::Color& outlineColor) const;
};