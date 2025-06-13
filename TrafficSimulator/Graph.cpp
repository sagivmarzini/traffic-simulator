#include "Graph.h"

Graph::Graph(const std::vector<sf::Vector2f>& points, const std::vector<Segment>& segments)
	: _points(points), _segments(segments)
{
}

void Graph::draw(Renderer& renderer) const
{
	for (const auto& segment : _segments)
	{
		segment.draw(renderer);
	}

	for (const auto& point : _points)
	{
		renderer.drawCircle(point, (int)Renderer::Default::PointRadius, 0, sf::Color::White);
	}
}