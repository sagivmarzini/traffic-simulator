#include "Graph.h"
#include "Random.h"

#include <exception>
#include <limits>

Graph::Graph(const std::vector<Point>& points, const std::vector<Segment>& segments)
	: _points(points), _segments(segments)
{
}

void Graph::addPoint(const Point& point)
{
	if (pointExists(point))
		throw std::invalid_argument("Point already exists on this graph");

	_points.push_back(point);
}

void Graph::addSegment(const Segment& segment)
{
	if (segmentExists(segment))
		throw std::invalid_argument("Segment already exists on this graph");

	_segments.push_back(segment);
}

void Graph::addRandomPoint(const sf::Vector2f& from, const sf::Vector2f& to)
{
	addPoint({ Random::floatInRange(from.x, to.x), Random::floatInRange(from.y, to.y) });
}

void Graph::addRandomSegment()
{
	if (_points.size() < 2)
		throw std::runtime_error("Not enough points to create a segment");

	const int maxAttempts = 100;
	for (int attempt = 0; attempt < maxAttempts; ++attempt)
	{
		auto& point1 = Random::randomItem(_points);
		auto& point2 = Random::randomItem(_points);

		if (point1 == point2)
			continue;

		Segment candidate(point1, point2);
		if (!segmentExists(candidate))
		{
			_segments.push_back(candidate);
			return;
		}
	}
}

void Graph::draw(Renderer& renderer) const
{
	for (const auto& segment : _segments)
	{
		segment.draw(renderer);
	}

	for (const auto& point : _points)
	{
		point.draw(renderer);
	}
}

std::vector<Point>& Graph::getPoints()
{
	return _points;
}

std::optional<size_t> Graph::getClosestPointIndex(const sf::Vector2f& position) const
{
	if (_points.empty()) return std::nullopt;

	float minDistance = std::numeric_limits<float>::max();
	float currentDistance = 0;
	std::optional<size_t> bestIndex;

	for (size_t i = 0; i < _points.size(); i++)
	{
		currentDistance = (_points[i] - position).lengthSquared();
		if (currentDistance < minDistance)
		{
			minDistance = currentDistance;
			bestIndex = i;
		}
	}

	return bestIndex;
}

bool Graph::pointExists(const Point& point) const
{
	return std::ranges::any_of(_points, [&point](const auto& p) { return p == point; });
}

bool Graph::segmentExists(const Segment& segment) const
{
	return std::ranges::any_of(_segments, [&segment](const auto& s) { return s == segment; });
}