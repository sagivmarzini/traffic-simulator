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
	else if (event.is<sf::Event::MouseButtonPressed>())
	{
		handleMouseClicked(*event.getIf<sf::Event::MouseButtonPressed>());
	}
	else if (event.is<sf::Event::MouseButtonReleased>())
	{
		handleMouseReleased(*event.getIf<sf::Event::MouseButtonReleased>());
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

	if (_dragging && _selectedPointIndex)
	{
		_graph.movePoint(*_selectedPointIndex, mousePosition);
		return;
	}

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
			_dragging = true;
			return;
		}

		_graph.addPoint(mousePosition);
		const auto lastPointIndex = _graph.getPoints().size() - 1;

		// Add a segment between selected point and the new one
		if (_selectedPointIndex)
		{
			_graph.addSegment(*_selectedPointIndex, lastPointIndex);
		}

		_selectedPointIndex = lastPointIndex;
	}
	else if (event.button == sf::Mouse::Button::Right)
	{
		if (_hoveredPointIndex)
		{
			const size_t removedIndex = *_hoveredPointIndex;

			_graph.removePoint(removedIndex);

			// Invalidate if selected point was deleted
			if (_selectedPointIndex && *_selectedPointIndex == removedIndex)
				_selectedPointIndex = std::nullopt;
			else if (_selectedPointIndex && *_selectedPointIndex > removedIndex)
				--*_selectedPointIndex; // Shift index left

			// Same logic for hover
			_hoveredPointIndex = std::nullopt;
		}
	}
}

void GraphEditor::handleMouseReleased(const sf::Event::MouseButtonReleased& event)
{
	if (event.button == sf::Mouse::Button::Left)
		_dragging = false;
}