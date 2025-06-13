#include "Button.h"

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& text, const sf::Font& font, const std::function<void()>& onClick)
	: _text(font, text, 24), _onClick(onClick)
{
	_rect.setPosition(position);
	_rect.setSize(size);
	_rect.setFillColor(sf::Color::Blue);
	_rect.setOutlineThickness(2);

	_text.setFillColor(sf::Color::White);

	sf::FloatRect textBounds = _text.getLocalBounds();
	_text.setOrigin(textBounds.getCenter());
	_text.setPosition(position + size / 2.f);
}

void Button::setCallback(const std::function<void()>& onClick)
{
	_onClick = onClick;
}

bool Button::isHovered(const sf::RenderWindow& window) const
{
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	return _rect.getGlobalBounds().contains(mousePos);
}

void Button::update(const sf::RenderWindow& window)
{
	bool hovered = isHovered(window);
	_rect.setFillColor(hovered ? sf::Color::Transparent : sf::Color::Blue);

	bool pressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	if (hovered && pressed && !_wasPressed && _onClick)
	{
		_onClick();
	}
	_wasPressed = pressed;
}

void Button::draw(sf::RenderWindow& window) const
{
	window.draw(_rect);
	window.draw(_text);
}