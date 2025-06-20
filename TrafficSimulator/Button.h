#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

class Button
{
public:
	Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& text, const sf::Font& font, const std::function<void()>& onClick);

	void setCallback(const std::function<void()>& onClick);
	bool handleEvent(const sf::Event& event);
	void draw(sf::RenderWindow& window) const;

	bool isHovered(const sf::Event& event) const;

private:
	sf::RectangleShape _rect;
	sf::Text _text;
	std::function<void()> _onClick;
	bool _wasPressed = false;
};
