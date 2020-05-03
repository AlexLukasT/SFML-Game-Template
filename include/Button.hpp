#ifndef BUTTON_H
#define BUTTON_H

#include<string>

#include"SFML\System.hpp"
#include"SFML\Window.hpp"
#include"SFML\Graphics.hpp"
#include"SFML\Audio.hpp"

enum buttonStates {BTN_IDLE = 0, BTN_HOVER = 1, BTN_ACTIVE = 2};

class Button
{
	// Create a clickable button
private:
	unsigned short buttonState;
	sf::RectangleShape shape;
	sf::Font font;
	sf::Text sfText;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:
	Button(float x, float y, float width, float height, std::string text,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	~Button();

	bool isPressed();

	void update(sf::Vector2f mousePos);
	void render(sf::RenderWindow* window);
};

#endif
