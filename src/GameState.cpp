#include"..\include\GameState.hpp"

GameState::GameState(sf::RenderWindow* window, float* dt, std::stack<State*>* states)
	:State(window, dt, 
		"C:/Users/AlexanderTemme/Projects/BattleChess/settings/keybinds_game.cfg",
		states)
{
	std::cout << "[GameState] State started" << std::endl;;

	this->initBackground(window);
}

GameState::~GameState()
{
}

void GameState::initBackground(sf::RenderWindow* window)
{
	sf::Vector2f windowSize;
	windowSize.x = window->getSize().x;
	windowSize.y = window->getSize().y;
	this->background.setSize(windowSize);
	this->background.setFillColor(sf::Color(150, 150, 150, 255));
}

void GameState::endState()
{
	std::cout << "[GameState] State stopped" << std::endl;
}

void GameState::checkKeyboardInputs()
{
	if (sf::Keyboard::isKeyPressed(this->getKey("ESCAPE")))
	{
		this->setQuit(true);
	}
}

void GameState::update()
{
	this->checkKeyboardInputs();
	this->updateMousePositions();
}

void GameState::render()
{
	this->window->draw(this->background);
}