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
		}
	}
}