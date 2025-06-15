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

bool Button::isHovered(const sf::Event& event) const
{
	auto mouseMoved = event.getIf<sf::Event::MouseMoved>();
	auto mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>();
	sf::Vector2f mousePos;

	if (mouseMoved)
	{
		mousePos = static_cast<sf::Vector2f>(mouseMoved->position);
		return _rect.getGlobalBounds().contains(mousePos);
	}
	else if (mouseButtonPressed)
	{
		mousePos = static_cast<sf::Vector2f>(mouseButtonPressed->position);
	}

	return _rect.getGlobalBounds().contains(mousePos);
}

bool Button::handleEvent(const sf::Event& event)
{
	// Handle mouse movement for hover state
	if (event.is<sf::Event::MouseMoved>())
	{
		bool hovered = isHovered(event);
		_rect.setFillColor(hovered ? sf::Color::Transparent : sf::Color::Blue);
	}

	// Handle mouse button press
	if (event.is<sf::Event::MouseButtonPressed>())
	{
		const auto& mouseEvent = event.getIf<sf::Event::MouseButtonPressed>();
		if ((*mouseEvent).button == sf::Mouse::Button::Left)
		{
			bool hovered = isHovered(event);
			if (hovered && _onClick)
			{
				_onClick();
				return true; // Button consumed the click event
			}
		}
	}

	return false; // Button didn't consume the event
}

void Button::draw(sf::RenderWindow& window) const
{
	// Save the current view
	sf::View currentView = window.getView();

	// Switch to default view for UI rendering (fixed to screen)
	window.setView(window.getDefaultView());

	// Draw the UI elements
	window.draw(_rect);
	window.draw(_text);

	// Restore the previous view
	window.setView(currentView);
}