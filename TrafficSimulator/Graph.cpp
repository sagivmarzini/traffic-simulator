#include "Graph.h"
#include "GraphJsonAdapters.h"
#include "Random.h"
#include "json.hpp"

#include <exception>
#include <limits>
#include <fstream>

using json = nlohmann::json;

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

void Graph::removePoint(size_t index)
{
	validatePointIndex(index);

	const auto& point = _points[index];
	for (auto it = _segments.begin(); it != _segments.end();)
	{
		if (it->contains(point))
			it = _segments.erase(it);
		else
			++it;
	}

	_points.erase(_points.begin() + index);
}

void Graph::movePoint(size_t index, const sf::Vector2f& newPosition)
{
	validatePointIndex(index);

	for (auto& segment : _segments)
	{
		if (segment.contains(_points[index]))
		{
			if (segment.p1 == _points[index])
				segment.p1 = newPosition;
			if (segment.p2 == _points[index])
				segment.p2 = newPosition;
		}
	}

	_points[index] = newPosition;
}

void Graph::addSegment(size_t indexPoint1, size_t indexPoint2)
{
	validatePointIndex(indexPoint1);
	validatePointIndex(indexPoint2);

	Segment segment(_points[indexPoint1], _points[indexPoint2]);

	if (segmentExists(segment))
		throw std::invalid_argument("This segment already exists on this graph");

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

void Graph::clear()
{
	_points.clear();
	_segments.clear();
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

void Graph::saveToFile(const std::string& filename) const
{
	json j;
	j["points"] = _points;
	j["segments"] = _segments;

	std::ofstream file(filename);
	if (!file)
		throw std::runtime_error("Failed to open file for saving.");

	file << j.dump(2); // 2 = pretty print indent
}

void Graph::loadFromFile(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file)
		throw std::runtime_error("Failed to open file for loading.");

	json j;
	file >> j;

	_points = j.at("points").get<std::vector<Point>>();
	_segments = j.at("segments").get<std::vector<Segment>>();
}

bool Graph::pointExists(const Point& point) const
{
	return std::ranges::any_of(_points, [&point](const auto& p) { return p == point; });
}

bool Graph::segmentExists(const Segment& segment) const
{
	return std::ranges::any_of(_segments, [&segment](const auto& s) { return s == segment; });
}

void Graph::validatePointIndex(size_t index) const
{
	if (index < 0 || index >= _points.size())
		throw std::out_of_range("Index is out of range");
}