#include <SFML/Graphics.hpp>
#include <iostream>

#include "Renderer.h"
#include "Segment.h"
#include "Graph.h"
#include "GraphEditor.h"
#include "Controls.h"
#include "Random.h"
#include "RoadNetwork.h"

constexpr auto WIDTH = 1080;
constexpr auto HEIGHT = 720;
constexpr auto saveFilename = "my-graph.json";

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

	std::vector<Node> points{
		Node(WIDTH / 4, HEIGHT / 4),
		Node(3 * WIDTH / 4, HEIGHT / 4),
		Node(WIDTH / 4, 3 * HEIGHT / 4),
		Node(3 * WIDTH / 4, 3 * HEIGHT / 4),
	};
	std::vector<Segment> segments{
		Segment(points[0], points[1]),
		Segment(points[1], points[2]),
		Segment(points[2], points[3])
	};
	Graph graph(points, segments);
	RoadNetwork roads(graph);
	graph.loadFromFile(saveFilename);
	GraphEditor graphEditor(graph, renderer.getWindow());

	Controls controls({ 0, HEIGHT - 100 }, WIDTH, 100);
	controls.addButton("Clear", [&graph]() {
		graph.clear();
		std::cout << "| GRAPH EDITOR | Graph cleared\n";
		}, font);
	controls.addButton("Save", [&graph]() {
		graph.saveToFile(saveFilename);
		std::cout << "| GRAPH EDITOR | Graph saved as `" << saveFilename << "`\n";
		}, font);

	while (renderer.isOpen())
	{
		while (auto event = renderer.getWindow().pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				renderer.getWindow().close();

			try
			{
				if (!controls.handleEvent(*event))
					graphEditor.handleEvent(*event);
			}
			catch (const std::exception& e)
			{
				std::cerr << "| GRAPH EDITOR ERROR | " << e.what() << '\n';
			}
		}

		renderer.clear(sf::Color(20, 20, 20));

		// UPDATE
		roads.setGraph(graph);

		// DRAW
		graph.draw(renderer);
		graphEditor.draw(renderer);
		roads.draw(renderer);
		controls.draw(renderer);

		renderer.display();
	}
}