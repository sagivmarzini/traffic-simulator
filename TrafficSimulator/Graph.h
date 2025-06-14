#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Segment.h"
#include "Point.h"
#include "Renderer.h"

class Graph
{
public:
	Graph(const std::vector<Point>& points = {}, const std::vector<Segment>& segments = {});

	// Throws exception if point already exists
	void addPoint(const Point& point);
	// Throws exception if segment already exists
	void addSegment(const Segment& segment);
	void addRandomPoint(const sf::Vector2f& from, const sf::Vector2f& to);
	void addRandomSegment();

	void draw(Renderer& renderer) const;

	std::vector<Point>& getPoints();
private:
	// TODO: Encapsulate point with dedicated class
	std::vector<Point> _points;
	std::vector<Segment> _segments;

	bool pointExists(const Point& point) const;
	bool segmentExists(const Segment& segment) const;
};
