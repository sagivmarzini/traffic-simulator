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
	void removePoint(size_t index);
	void movePoint(size_t index, const sf::Vector2f& newPosition);

	// Throws exception if segment already exists
	void addSegment(size_t indexPoint1, size_t indexPoint2);
	void addRandomPoint(const sf::Vector2f& from, const sf::Vector2f& to);
	void addRandomSegment();

	void clear();

	void draw(Renderer& renderer) const;

	std::vector<Point>& getPoints();
	std::optional<size_t> getClosestPointIndex(const sf::Vector2f& position) const;

	void saveToFile(const std::string& filename) const;
	void loadFromFile(const std::string& filename);
private:
	std::vector<Point> _points;
	std::vector<Segment> _segments;

	bool pointExists(const Point& point) const;
	bool segmentExists(const Segment& segment) const;

	void validatePointIndex(size_t index) const;
};
