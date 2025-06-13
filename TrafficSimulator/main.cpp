#include <SFML/Graphics.hpp>
#include <iostream>

#include "Renderer.h"
#include "Segment.h"
#include "Graph.h"
#include "Controls.h"

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
		sf::Vector2f(200, 200),
		sf::Vector2f(500, 200),
		sf::Vector2f(400, 400),
		sf::Vector2f(100, 300),
	};
	std::vector<Segment> segments{
		Segment(points[0], points[1]),
		Segment(points[2], points[3]),
		Segment(points[1], points[3]),
	};
	Graph graph(points, segments);

	Controls controls({ 0, HEIGHT - 100 }, WIDTH, 100);
	controls.addButton("Test!", []() {std::cout << "Test button clicked!\n";}, font);

	while (renderer.isOpen())
	{
		renderer.processEvents();
		renderer.clear(sf::Color(20, 20, 20));

		controls.update(renderer.getWindow());

		graph.draw(renderer);
		controls.draw(renderer);

		renderer.display();
	}
}