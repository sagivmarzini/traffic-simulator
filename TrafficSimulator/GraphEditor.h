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

	Point* getSelectedPoint() const;
};
