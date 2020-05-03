#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include"GameState.hpp"
#include"Button.hpp"

class MainMenuState : public State
{
	// Main class for running the actual game
private:
	sf::RectangleShape background;
	std::map<std::string, Button*> buttons;

	//initializers
	void initBackground(sf::RenderWindow* window);
	void initButtons();

public:
	MainMenuState(sf::RenderWindow* window, float* dt, std::stack<State*>* states);
	~MainMenuState();

	void endState();
	void checkKeyboardInputs();
	void updateButtons();
	void update();
	void render();
};

#endif
