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
		Point mousePosition = _window.mapPixelToCoords({ mouseButton.position.x, mouseButton.position.y });

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
		selectedPoint->drawWithOutline(renderer, 4, sf::Color::Red);
}

Point* GraphEditor::getSelectedPoint() const
{
	auto& points = _graph.getPoints();

	if (_selectedPointIndex && *_selectedPointIndex < points.size())
		return &points[*_selectedPointIndex];

	return nullptr;
}