#pragma once

#include <SFML/Graphics.hpp>

#include "Graph.h"
#include "Point.h"

class GraphEditor
{
public:
	GraphEditor(Graph& graph, sf::RenderWindow& window);

	void handleEvent(const sf::Event& event);

	void draw(Renderer& renderer) const;

private:
	Graph& _graph;
	sf::RenderWindow& _window;
	std::optional<size_t> _selectedPointIndex;
	std::optional<size_t> _hoveredPointIndex;

	Point* getSelectedPoint() const;
	Point* getHoveredPoint() const;

	void handleMouseMoved(const sf::Event::MouseMoved& event);
	void handleMouseClicked(const sf::Event::MouseButtonPressed& event);
};
