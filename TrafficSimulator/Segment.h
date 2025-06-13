#pragma once

#include <SFML/Graphics.hpp>

#include "Renderer.h"

struct Segment
{
	sf::Vector2f p1;
	sf::Vector2f p2;

	Segment(const sf::Vector2f& p1, const sf::Vector2f& p2);

	void draw(Renderer& renderer) const;

	bool operator==(const Segment& other) const;
	bool contains(const sf::Vector2f& point) const;
};