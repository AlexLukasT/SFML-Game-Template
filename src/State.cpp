#include"..\include\State.hpp"

State::State(sf::RenderWindow* window, float* dt, std::string keyFile,
	std::stack<State*>* states)
{
	this->window = window;
	this->dt = dt;
	this->states = states;
	this->quit = false;
	this->supportedKeys = { "Escape", "W", "A", "S", "D" };
	this->supportedKeyNums = { 36, 22, 0, 18, 3 };

	this->initKeyBindings(keyFile);
}

State::~State()
{
}

const bool& State::getQuit() const
{
	return this->quit;
}

void State::setQuit(const bool& quit)
{
	this->quit = quit;
}

void State::initKeyBindings(std::string keyFile)
{
	// supported keys
	std::map<std::string, int> supportedKeysMap;

	for (int i = 0; i < this->supportedKeys.size(); i++)
	{
		supportedKeysMap[this->supportedKeys[i]] = this->supportedKeyNums[i];
	}

	std::ifstream ifs(keyFile);

	std::string action;
	std::string sfKey;

	while (ifs >> action >> sfKey)
	{
		if (!supportedKeysMap[sfKey] && sfKey != "A")
		{
			// check if the specified key is supported (see loadSupportedKeys),
			// because the number for the key "A" is 0, which is also the
			// default value when a key does not exist, it has to be checked
			throw("Error::State::Not supported key: " + sfKey);
		}
		else
		{	
			this->keyMap[action] = supportedKeysMap[sfKey];
		}
	}
}

sf::Keyboard::Key State::getKey(std::string action)
{
	if (this->keyMap.find(action) == this->keyMap.end())
	{
		// action is not a defined key
		throw("Error::State::Invalid action: " + action);
	}
	return sf::Keyboard::Key(this->keyMap[action]);
}

void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}