#include"..\include\Button.hpp"

Button::Button(float x, float y, float width, float height,std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->buttonState = BTN_IDLE;
	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idleColor);
	this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setOutlineThickness(1.f);

	if (!this->font.loadFromFile("fonts/Dosis-Light.ttf"))
	{
		throw("Error::Button::Could not load font");
	}

	this->sfText.setFont(this->font);
	this->sfText.setString(text);
	this->sfText.setCharacterSize(50);
	this->sfText.setStyle(sf::Text::Bold);
	this->sfText.setFillColor(sf::Color::White);
	// TODO: Check the text centered in y direction
	this->sfText.setPosition(sf::Vector2f(
		x + (width / 2.f) - (this->sfText.getGlobalBounds().width / 2.f),
		y + (height / 2.f) - (this->sfText.getGlobalBounds().height / 1.3)
	));
}

Button::~Button()
{

}

void Button::update(sf::Vector2f mousePos)
{
	// idle
	this->buttonState = BTN_IDLE;

	// hover
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		// click
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	// update button colors based on button state
	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		break;

	default:
		// this point should never be reached
		this->shape.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::render(sf::RenderWindow* window)
{
	window->draw(this->shape);
	window->draw(this->sfText);
}

bool Button::isPressed()
{
	return this->buttonState == BTN_ACTIVE;
}