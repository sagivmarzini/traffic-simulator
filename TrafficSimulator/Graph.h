#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Segment.h"
#include "Renderer.h"

class Graph
{
public:
	Graph(const std::vector<sf::Vector2f>& points = {}, const std::vector<Segment>& segments = {});

	void draw(Renderer& renderer) const;
private:
	std::vector<sf::Vector2f> _points;
	std::vector<Segment> _segments;
};
