#ifndef STATE_H
#define STATE_H

#include"SFML\System.hpp"
#include"SFML\Window.hpp"
#include"SFML\Graphics.hpp"
#include"SFML\Audio.hpp"
#include"SFML\Network.hpp"

#include<iostream>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include<stack>
#include<string>
#include<vector>
#include<math.h>

class State
{
	// Abstract base class for multiple states of the game
private:
	bool quit;

protected:
	sf::RenderWindow* window;  // Main window
	float* dt;  // Datetime to make movement independent of frames

	std::stack<State*> *states;

	std::vector<std::string> supportedKeys;
	std::vector<int> supportedKeyNums;
	std::map<std::string, int> keyMap;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// initializers
	void initKeyBindings(std::string keyFile);

public:
	// constructor, destructor
	State(sf::RenderWindow* window, float* dt, std::string keyFile, 
		std::stack<State*>* states);
	virtual ~State();

	// getters, setters
	const bool& getQuit() const;
	void setQuit(const bool& quit);
	sf::Keyboard::Key getKey(std::string action);

	// regular functions
	void updateMousePositions();

	// virtual functions
	virtual void checkKeyboardInputs() = 0;
	virtual void endState() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};

#endif 