#include "GraphEditor.h"

GraphEditor::GraphEditor(Graph& graph, sf::RenderWindow& window)
	: _graph(graph), _window(window)
{
}

void GraphEditor::handleEvent(const sf::Event& event)
{
	// Mouse events
	if (event.is<sf::Event::MouseMoved>())
		handleMouseMoved(*event.getIf<sf::Event::MouseMoved>());
	else if (event.is<sf::Event::MouseButtonPressed>())
		handleMouseClicked(*event.getIf<sf::Event::MouseButtonPressed>());
	else if (event.is<sf::Event::MouseButtonReleased>())
		handleMouseReleased(*event.getIf<sf::Event::MouseButtonReleased>());
	else if (event.is<sf::Event::MouseWheelScrolled>())
		handleMouseScroll(*event.getIf<sf::Event::MouseWheelScrolled>());

	// Keyboard events
	else if (event.is<sf::Event::KeyPressed>())
		handleKeyPressed(*event.getIf<sf::Event::KeyPressed>());
	else if (event.is<sf::Event::KeyReleased>())
		handleKeyReleased(*event.getIf<sf::Event::KeyReleased>());
}

void GraphEditor::draw(Renderer& renderer) const
{
	if (auto selectedPoint = getSelectedPoint())
	{
		selectedPoint->drawWithOutline(renderer, 6, sf::Color(255, 0, 0));

		// Draw preview segment from selected point to mouse or to hovered point
		if (_hoveredPointIndex && *_hoveredPointIndex != *_selectedPointIndex && _shiftDown)
		{
			const auto& target = _graph.getPoints()[*_hoveredPointIndex];
			Segment(*selectedPoint, target).draw(renderer, 80);
		}
		else if (*selectedPoint != _mousePosition && !_hoveredPointIndex)
		{
			Segment(*selectedPoint, _mousePosition).draw(renderer, 50);
		}
	}

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
	_mousePosition = _window.mapPixelToCoords({ event.position.x, event.position.y });

	// Drag selected point if dragging
	if (_dragging && _selectedPointIndex)
	{
		try
		{
			_graph.movePoint(*_selectedPointIndex, _mousePosition);
		}
		catch (const std::exception& e)
		{
			_selectedPointIndex = std::nullopt;
		}
		return;
	}

	// Mark a close point as hovered
	if (const auto closestPointIndex = _graph.getClosestPointIndex(_mousePosition);
		closestPointIndex &&
		(_graph.getPoints()[*closestPointIndex] - _mousePosition).length() <= 2 * (int)Renderer::Default::PointRadius)
	{
		_hoveredPointIndex = closestPointIndex;
	}
	else
	{
		_hoveredPointIndex = std::nullopt;
	}

	// Pan the view if holding middle mouse
	if (_panning)
	{
		// Calculate delta in screen space
		sf::Vector2i currentPixel = { event.position.x, event.position.y };
		sf::Vector2f pixelDelta(_panAnchor - currentPixel);

		sf::View view = _window.getView();

		// Convert pixel delta to world delta based on current zoom level
		sf::Vector2f worldDelta = pixelDelta * (view.getSize().x / _window.getSize().x);

		view.move(worldDelta);
		_window.setView(view);

		// Update anchor to current pixel position
		_panAnchor = currentPixel;
	}
}

void GraphEditor::handleMouseClicked(const sf::Event::MouseButtonPressed& event)
{
	if (event.button == sf::Mouse::Button::Left)
		handleLeftClick(event);
	else if (event.button == sf::Mouse::Button::Right)
		handleRightClick(event);
	else if (event.button == sf::Mouse::Button::Middle)
		handleMiddleClick(event);
}

void GraphEditor::handleMouseReleased(const sf::Event::MouseButtonReleased& event)
{
	if (event.button == sf::Mouse::Button::Left)
		_dragging = false;
	if (event.button == sf::Mouse::Button::Middle)
		_panning = false;
}

void GraphEditor::handleLeftClick(const sf::Event::MouseButtonPressed& event)
{
	if (_hoveredPointIndex)
	{
		if (_shiftDown && _selectedPointIndex && _hoveredPointIndex != _selectedPointIndex)
			_graph.addSegment(*_selectedPointIndex, *_hoveredPointIndex);

		_dragging = true;
		_selectedPointIndex = _hoveredPointIndex;
		return;
	}

	_graph.addPoint(_mousePosition);
	const auto lastPointIndex = _graph.getPoints().size() - 1;

	// Add a segment between selected point and the new one
	if (_selectedPointIndex)
	{
		try
		{
			_graph.addSegment(*_selectedPointIndex, lastPointIndex);
		}
		catch (...)
		{
			_selectedPointIndex = std::nullopt;
		}
	}

	_selectedPointIndex = lastPointIndex;
}

void GraphEditor::handleRightClick(const sf::Event::MouseButtonPressed& event)
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
	else
	{
		_selectedPointIndex = std::nullopt;
	}
}

void GraphEditor::handleMiddleClick(const sf::Event::MouseButtonPressed& event)
{
	_panning = true;
	_panAnchor = _window.mapCoordsToPixel(_mousePosition);
}

void GraphEditor::handleMouseScroll(const sf::Event::MouseWheelScrolled& event)
{
	// Zoom to the mouse
	sf::View view = _window.getView();

	sf::Vector2f beforeZoom = _window.mapPixelToCoords({ event.position.x, event.position.y });
	view.zoom(event.delta > 0 ? 0.9f : 1.1f);
	_window.setView(view);

	sf::Vector2f afterZoom = _window.mapPixelToCoords({ event.position.x, event.position.y });
	sf::Vector2f offset = beforeZoom - afterZoom;
	view.move(offset);

	_window.setView(view);
}

void GraphEditor::handleKeyPressed(const sf::Event::KeyPressed& event)
{
	if (event.code == sf::Keyboard::Key::LShift)
		_shiftDown = true;
}

void GraphEditor::handleKeyReleased(const sf::Event::KeyReleased& event)
{
	if (event.code == sf::Keyboard::Key::LShift)
		_shiftDown = false;
}