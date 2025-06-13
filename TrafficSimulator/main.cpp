#include <SFML/Graphics.hpp>
#include <iostream>

#include "Renderer.h"
#include "Segment.h"
#include "Graph.h"
#include "GraphEditor.h"
#include "Controls.h"
#include "Random.h"

constexpr auto WIDTH = 1080;
constexpr auto HEIGHT = 720;

static sf::Font loadFont(const std::string& fontName)
{
	sf::Font font;

	if (!font.openFromFile(fontName))
	{
		throw std::runtime_error("Couldn't load font");
	}

	return font;
}

int main()
{
	Renderer renderer(sf::VideoMode{ {WIDTH, HEIGHT } }, "Traffic Simulator");
	sf::Font font = loadFont("heebo.ttf");

	std::vector<sf::Vector2f> points{
		sf::Vector2f(WIDTH / 4, HEIGHT / 4),
		sf::Vector2f(3 * WIDTH / 4, HEIGHT / 4),
		sf::Vector2f(WIDTH / 4, 3 * HEIGHT / 4),
		sf::Vector2f(3 * WIDTH / 4, 3 * HEIGHT / 4),
	};
	Graph graph(points);
	GraphEditor graphEditor(graph, renderer.getWindow());

	Controls controls({ 0, HEIGHT - 100 }, WIDTH, 100);

	while (renderer.isOpen())
	{
		while (auto event = renderer.getWindow().pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				renderer.getWindow().close();

			try
			{
				graphEditor.handleEvent(*event);
			}
			catch (const std::exception& e)
			{
				std::cerr << "Error editing graph: " << e.what() << '\n';
			}
		}

		renderer.clear(sf::Color(20, 20, 20));

		// UPDATE

		// DRAW
		graph.draw(renderer);
		graphEditor.draw(renderer);
		controls.draw(renderer);

		renderer.display();
	}
}