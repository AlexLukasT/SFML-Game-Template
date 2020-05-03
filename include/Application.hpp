#ifndef APPLICATION_H
#define APPLICATION_H

#include"MainMenuState.hpp"

class Application 
{
private:
	std::vector<sf::VideoMode> videoModes;
	sf::RenderWindow* window;
	sf::Event sfEvent;

	sf::Clock totalClock;
	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	bool showFps;
	sf::Font font;
	sf::Text fpsText;

	//functions
	void initWindow();
	void initVariables();
	void initStates();
	void initFpsText();

public:
	Application();
	~Application();

	void updateDt();
	void updateFps();
	void updateSFMLEvents();
	void updateStates();
	void update();
	void render();
	void quit();
	void run();
};

#endif