#include "stdafx.h"
#include "MainMenuState.h"


//INITIALIZER FUNCTIONS
void MainMenuState::initVariables()
{

}
void MainMenuState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x), 
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg1.jpg")) 
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);
}
void MainMenuState::initFonts()
{
	if (
		!this->font.loadFromFile("Fonts/ComicNeue.ttf")) 
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}



}
void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

	if (ifs.is_open()) {
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2) {
			this->keybinds[key] = this->supportedKeys->at(key2);
		}

	}

	ifs.close();
}
void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new gui::Button(
		100.f, 100.f, 150.f, 50.f,
		&this->font, "New Game", 24,
		sf::Color(223, 230, 233, 200), sf::Color(250, 250, 250, 250), sf::Color(223, 230, 233, 200),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
		);
	
	this->buttons["SETTINGS_STATE"] = new gui::Button(
		100.f, 175.f, 150.f, 50.f,
		&this->font, "Settings", 24,
		sf::Color(223, 230, 233, 200), sf::Color(250, 250, 250, 250), sf::Color(223, 230, 233, 200),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
		);

	this->buttons["EDITOR_STATE"] = new gui::Button(
		100.f, 250.f, 150.f, 50.f,
		&this->font, "Editor", 24,
		sf::Color(223, 230, 233, 200), sf::Color(250, 250, 250, 250), sf::Color(223, 230, 233, 200),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
		);
	
	this->buttons["EXIT_STATE"] = new gui::Button(
		100.f, 400.f, 150.f, 50.f,
		&this->font, "Quit", 24,
		sf::Color(223, 230, 233, 200), sf::Color(250, 250, 250, 250), sf::Color(223, 230, 233, 200),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
		);
}

// CONSTRUCTOR / DESTRUCTOR
MainMenuState::MainMenuState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}
MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end() ; ++it)
	{
		delete it->second;
	}
}

// FUNCTIONS
void MainMenuState::updateInput(const float& dt)
{
}
void MainMenuState::updateButtons()
{
	/*UPDATE ALL THE BUTTONS IN THE STATE AND HANDLES THEIR FUNCTIONLAITY*/
	for (auto &it : this->buttons) 
	{
		it.second->update(this->mousePosWindow);
	}

	//NEW GAME
	if (this->buttons["GAME_STATE"]->isPressed()) 
	{
		this->states->push(new GameState(this->stateData));
	}

	if (this->buttons["SETTINGS_STATE"]->isPressed())
	{
		this->states->push(new SettingsState(this->stateData));
	}

	// EDITOR STATE
	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->states->push(new EditorState(this->stateData));
	}

	//QUIT THE GAME
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}
void MainMenuState::update(const float& dt)
{
	this->updateInput(dt);
	this->updateMousePositions();

	this->updateButtons();
}
void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}
void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);
	this->renderButtons(*target);
	
}
