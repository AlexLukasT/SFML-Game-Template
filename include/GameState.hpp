#ifndef GAME_H
#define GAME_H

#include"State.hpp"

class GameState: public State
{
	// Main class for running the actual game
private:
	sf::RectangleShape background;

	// initializers
	void initBackground(sf::RenderWindow* window);

public:
	GameState(sf::RenderWindow* window, float* dt, std::stack<State*>* states);
	~GameState();

	void endState();
	void checkKeyboardInputs();
	void update();
	void render();
};

#endif
