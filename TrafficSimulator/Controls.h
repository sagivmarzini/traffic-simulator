#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Renderer.h"

class Controls
{
public:
	Controls(const sf::Vector2f& position, float width, float height);

	void addButton(const std::string& text, const std::function<void()>& onClick, const sf::Font& font);
	void draw(Renderer& renderer) const;
	void update(const sf::RenderWindow& window);
private:
	sf::Vector2f _position; // Top left corner position
	float _width;
	float _height;
	std::vector<Button> _buttons;
};
