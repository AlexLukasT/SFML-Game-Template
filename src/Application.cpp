#include"..\include\Application.hpp"

Application::Application() 
{
	std::cout << "[Application] Start" << std::endl;
	this->initVariables();
	this->initWindow();
	this->initStates();
	if (this->showFps)
		this->initFpsText();
}

Application::~Application() 
{
	// delete object created in constructor with "new"
	delete this->window;

	while (!this->states.empty())
	{	
		// empty the states by deleting the objects and pointers
		delete this->states.top();
		this->states.pop();
	}
}

// initializers
void Application::initWindow()
{
	// Initialize the window with settings from graphics.cfg
	std::ifstream ifs("C:/Users/AlexanderTemme/Projects/BattleChess/settings/graphics.cfg");

	this->videoModes = sf::VideoMode::getFullscreenModes();

	std::string temp;  // dummy variable to store the option names in
	sf::VideoMode windowSize = sf::VideoMode::getDesktopMode();
	bool fullscreen = false;
	unsigned frameRateLimit = 60;
	bool vSyncEnabled = false;
	unsigned antialisingLevel = 0;

	if (ifs.is_open())
	{
		ifs >> temp >> windowSize.width >> windowSize.height;
		ifs >> temp >> fullscreen;
		ifs >> temp >> frameRateLimit;
		ifs >> temp >> vSyncEnabled;
		ifs >> temp >> antialisingLevel;
		ifs >> temp >> this->showFps;
	}

	ifs.close();

	sf::ContextSettings windowSettings;
	windowSettings.antialiasingLevel = antialisingLevel;

	if (fullscreen)
		this->window = new sf::RenderWindow(windowSize, "BattleChess", 
			sf::Style::Fullscreen, windowSettings);
	else
		this->window = new sf::RenderWindow(windowSize, "BattleChess",
			sf::Style::Default, windowSettings);
	this->window->setFramerateLimit(frameRateLimit);
	this->window->setVerticalSyncEnabled(vSyncEnabled);
}

void Application::initVariables() 
{
	this->window = NULL;
	this->dt = 0.f;
}

void Application::initStates()
{
	// Start in state main menu
	MainMenuState* mainMenuState = new MainMenuState(this->window, 
		&this->dt, &this->states);
	this->states.push(mainMenuState);
}

void Application::initFpsText()
{
	if (!this->font.loadFromFile("fonts/Dosis-Light.ttf"))
		throw "Error::Application::Could not load font";
	this->fpsText.setFont(this->font);
	this->fpsText.setCharacterSize(20);
	this->fpsText.setString("120");
	this->fpsText.setFillColor(sf::Color::Green);
	this->fpsText.setPosition(
		this->window->getSize().x - this->fpsText.getGlobalBounds().width, 0
	);
}

// functions
void Application::updateDt() 
{
	// Update DateTime with the time to update and render one frame
	this->dt = this->dtClock.restart().asSeconds();
}

void Application::updateFps()
{
	if (fmod(this->totalClock.getElapsedTime().asSeconds(), 1.f) <= 0.1)
	{
		// update the frame counter approximately every second (and not every frame)
		this->fpsText.setString(std::to_string(static_cast<int>(1 / this->dt)));
	}
}

void Application::updateSFMLEvents() 
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed) 
		{
			this->quit();
		}
	}
}

void Application::updateStates()
{
	if (this->states.empty())
	{
		// No states existing -> close window
		this->quit();
	} 
	else
	{
		// Get the current running state, which is on top of the stack
		State* currentState = this->states.top();
		currentState->update();

		if (currentState->getQuit())
		{
			// State wants to quit
			currentState->endState();
			delete currentState;
			this->states.pop();
		}
	}
}

void Application::update() 
{
	this->updateDt();
	this->updateFps();
	this->updateSFMLEvents();
	this->updateStates();
}

void Application::render() 
{
	this->window->clear();

	if (!this->states.empty())
		this->states.top()->render();

	if (this->showFps)
		this->window->draw(this->fpsText);

	this->window->display();
}

void Application::run() 
{
	int counter = 0;
	while (this->window->isOpen()) 
	{
		this->update();
		this->render();
		counter++;
	}
}

void Application::quit()
{
	std::cout << "[Application] Quit" << std::endl;
	this->window->close();
}