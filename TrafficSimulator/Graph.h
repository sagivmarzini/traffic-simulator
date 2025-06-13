#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Segment.h"
#include "Renderer.h"

class Graph
{
public:
	Graph(const std::vector<sf::Vector2f>& points = {}, const std::vector<Segment>& segments = {});

	// Throws exception if point already exists
	void addPoint(const sf::Vector2f& point);
	// Throws exception if segment already exists
	void addSegment(const Segment& segment);
	void addRandomPoint(const sf::Vector2f& from, const sf::Vector2f& to);
	void addRandomSegment();

	void draw(Renderer& renderer) const;

	std::vector<sf::Vector2f>& getPoints();
private:
	// TODO: Encapsulate point with dedicated class
	std::vector<sf::Vector2f> _points;
	std::vector<Segment> _segments;

	bool pointExists(const sf::Vector2f& point) const;
	bool segmentExists(const Segment& segment) const;
};
