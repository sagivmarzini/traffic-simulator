#pragma once

#include <SFML/Graphics.hpp>

#include "Renderer.h"

struct Segment
{
	sf::Vector2f p1;
	sf::Vector2f p2;

	Segment(const sf::Vector2f& p1, const sf::Vector2f& p2);

	void draw(Renderer& renderer) const;
};