#pragma once

#include <SFML/Graphics.hpp>

#include "Graph.h"

class GraphEditor
{
public:
	GraphEditor(Graph& graph, sf::RenderWindow& window);

	void handleEvent(const sf::Event& event);

private:
	Graph& _graph;
	sf::RenderWindow& _window;
};
