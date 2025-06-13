#include "GraphEditor.h"

GraphEditor::GraphEditor(Graph& graph, sf::RenderWindow& window)
	: _graph(graph), _window(window)
{
}

void GraphEditor::handleEvent(const sf::Event& event)
{
	if (event.is<sf::Event::MouseButtonPressed>())
	{
		auto& mouseButton = *event.getIf<sf::Event::MouseButtonPressed>();
		sf::Vector2f mousePosition = _window.mapPixelToCoords({ mouseButton.position.x, mouseButton.position.y });

		if (mouseButton.button == sf::Mouse::Button::Left)
		{
			_graph.addPoint(mousePosition);
			_selectedPointIndex = _graph.getPoints().size() - 1;
		}
	}
}

void GraphEditor::draw(Renderer& renderer) const
{
	auto selectedPoint = getSelectedPoint();
	if (selectedPoint)
		renderer.drawCircle(*selectedPoint, (int)Renderer::Default::PointRadius, 0, sf::Color::Red);
}

sf::Vector2f* GraphEditor::getSelectedPoint() const
{
	auto& points = _graph.getPoints();

	if (_selectedPointIndex && *_selectedPointIndex < points.size())
		return &points[*_selectedPointIndex];

	return nullptr;
}