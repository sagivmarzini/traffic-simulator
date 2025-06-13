#include "Controls.h"

Controls::Controls(const sf::Vector2f& position, float width, float height)
	: _position(position), _width(width), _height(height)
{
}

void Controls::addButton(const std::string& text, const std::function<void()>& onClick, const sf::Font& font)
{
	_buttons.push_back(
		Button({ _position.x + _height * _buttons.size(), _position.y }, { _height, _height }, text, font, onClick)
	);
}

void Controls::draw(Renderer& renderer) const
{
	for (const auto& button : _buttons)
	{
		button.draw(renderer.getWindow());
	}
}

void Controls::update(const sf::RenderWindow& window)
{
	for (auto& button : _buttons)
	{
		button.update(window);
	}
}