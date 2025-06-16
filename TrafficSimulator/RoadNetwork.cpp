#include "RoadNetwork.h"

RoadNetwork::RoadNetwork(const Graph& graph)
	: _graph(graph)
{
}

void RoadNetwork::setGraph(const Graph& graph)
{
	_graph = graph;
}

void RoadNetwork::draw(Renderer& renderer) const
{
	for (const auto& segment : _graph.getSegments())
	{
		sf::Vector2f start = segment.p1;
		sf::Vector2f end = segment.p2;

		// Calculate direction and perpendicular vectors
		sf::Vector2f direction = end - start;
		float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

		if (length == 0.0f) return;

		direction /= length; // Normalize
		sf::Vector2f perpendicular(-direction.y, direction.x); // 90 degrees rotated

		// Calculate the four corners of the road rectangle
		sf::Vector2f halfWidth = perpendicular * (_roadWidth / 2.0f);
		sf::Vector2f topLeft = start - halfWidth;
		sf::Vector2f topRight = start + halfWidth;
		sf::Vector2f bottomLeft = end - halfWidth;
		sf::Vector2f bottomRight = end + halfWidth;

		// Draw the road as a filled rectangle
		sf::ConvexShape road(4);
		road.setPoint(0, topLeft);
		road.setPoint(1, topRight);
		road.setPoint(2, bottomRight);
		road.setPoint(3, bottomLeft);
		road.setFillColor(sf::Color(64, 64, 64)); // Dark gray road color

		renderer.getWindow().draw(road);

		// Draw center dashed line
		sf::Vector2f centerStart = start;
		sf::Vector2f centerEnd = end;
		renderer.drawDashedLine(centerStart, centerEnd, 2.0f, sf::Color::White, 20.0f, 10.0f);

		// Draw road edges
		renderer.drawLine(topLeft, bottomLeft, 1.0f, sf::Color::White);
		renderer.drawLine(topRight, bottomRight, 1.0f, sf::Color::White);
	}
}