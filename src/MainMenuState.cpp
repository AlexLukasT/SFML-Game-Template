#include"..\include\MainMenuState.hpp"
#include"..\include\Button.hpp"

MainMenuState::MainMenuState(sf::RenderWindow* window, float* dt,
	std::stack<State*>* states)
	:State(window, dt, 
		"C:/Users/AlexanderTemme/Projects/BattleChess/settings/keybinds_menu.cfg",
		states)
{
	std::cout << "[MainMenuState] State started" << std::endl;;

	this->initBackground(window);
	this->initButtons();
}

MainMenuState::~MainMenuState()
{
	// Delete all the button pointers
	for (auto& it : this->buttons)
	{
		delete it.second;
	}
}

void MainMenuState::initBackground(sf::RenderWindow* window)
{
	sf::Vector2f windowSize;
	windowSize.x = window->getSize().x;
	windowSize.y = window->getSize().y;
	this->background.setSize(windowSize);
	this->background.setFillColor(sf::Color::Blue);
}

void MainMenuState::initButtons()
{
	int centerX = this->window->getSize().x / 2.f - 300 / 2.f;
	this->buttons["start"] = new Button(centerX, 200, 300, 100, "Start Game",
		sf::Color(88, 27, 158, 255),
		sf::Color(140, 90, 199, 255),
		sf::Color(30, 8, 56, 255));

	this->buttons["quit"] = new Button(centerX, 400, 300, 100, "Quit",
		sf::Color(88, 27, 158, 255),
		sf::Color(140, 90, 199, 255),
		sf::Color(30, 8, 56, 255));
}

void MainMenuState::endState()
{
	std::cout << "[MainMenuState] State stopped" << std::endl;
}

void MainMenuState::checkKeyboardInputs()
{
}

void MainMenuState::updateButtons()
{
	for (auto it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	if (this->buttons["start"]->isPressed())
		// Start the game -> push new GameStates to the states stack
		this->states->push(new GameState(this->window, this->dt, this->states));

	if (this->buttons["quit"]->isPressed())
		this->setQuit(true);
}

void MainMenuState::update()
{
	this->checkKeyboardInputs();
	this->updateMousePositions();

	this->updateButtons();
}

void MainMenuState::render()
{
	this->window->draw(this->background);
	for (auto& it : this->buttons)
	{
		it.second->render(this->window);
	}
}