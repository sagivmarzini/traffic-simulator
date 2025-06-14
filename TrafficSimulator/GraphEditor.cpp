#include "GraphEditor.h"

GraphEditor::GraphEditor(Graph& graph, sf::RenderWindow& window)
	: _graph(graph), _window(window)
{
}

void GraphEditor::handleEvent(const sf::Event& event)
{
	if (event.is<sf::Event::MouseMoved>())
	{
		handleMouseMoved(*event.getIf<sf::Event::MouseMoved>());
	}

	if (event.is<sf::Event::MouseButtonPressed>())
	{
		handleMouseClicked(*event.getIf<sf::Event::MouseButtonPressed>());
	}
}

void GraphEditor::draw(Renderer& renderer) const
{
	if (auto selectedPoint = getSelectedPoint())
		selectedPoint->drawWithOutline(renderer, 6, sf::Color(255, 0, 0));

	if (auto hoveredPoint = getHoveredPoint())
		hoveredPoint->drawWithOutline(renderer, 8, sf::Color(255, 0, 0, 100));
}

Point* GraphEditor::getSelectedPoint() const
{
	auto& points = _graph.getPoints();

	if (_selectedPointIndex && *_selectedPointIndex < points.size())
		return &points[*_selectedPointIndex];

	return nullptr;
}

Point* GraphEditor::getHoveredPoint() const
{
	auto& points = _graph.getPoints();

	if (_hoveredPointIndex && *_hoveredPointIndex < points.size())
		return &points[*_hoveredPointIndex];

	return nullptr;
}

void GraphEditor::handleMouseMoved(const sf::Event::MouseMoved& event)
{
	sf::Vector2f mousePosition = _window.mapPixelToCoords({ event.position.x, event.position.y });

	if (const auto closestPointIndex = _graph.getClosestPointIndex(mousePosition);
		closestPointIndex &&
		(_graph.getPoints()[*closestPointIndex] - mousePosition).length() <= 2 * (int)Renderer::Default::PointRadius)
	{
		_hoveredPointIndex = closestPointIndex;
	}
	else
	{
		_hoveredPointIndex = std::nullopt;
	}
}

void GraphEditor::handleMouseClicked(const sf::Event::MouseButtonPressed& event)
{
	sf::Vector2f mousePosition = _window.mapPixelToCoords({ event.position.x, event.position.y });

	if (event.button == sf::Mouse::Button::Left)
	{
		if (_hoveredPointIndex)
		{
			_selectedPointIndex = _hoveredPointIndex;
			return;
		}

		_graph.addPoint(mousePosition);
		_selectedPointIndex = _graph.getPoints().size() - 1;
	}
}