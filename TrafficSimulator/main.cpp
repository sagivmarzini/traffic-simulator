#include <SFML/Graphics.hpp>
#include <iostream>

#include "Renderer.h"
#include "Segment.h"
#include "Graph.h"
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

	Controls controls({ 0, HEIGHT - 100 }, WIDTH, 100);
	controls.addButton("Random\nPoint", [&graph]() {graph.addRandomPoint({ 0,0 }, { WIDTH, HEIGHT });}, font);
	controls.addButton("Random\nSegment", [&graph]() {graph.addRandomSegment();}, font);

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