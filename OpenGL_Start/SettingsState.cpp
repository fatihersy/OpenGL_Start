#include "stdafx.h"
#include "SettingsState.h"

//INITIALIZER FUNCTIONS
void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
}
void SettingsState::initBackground()
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
void SettingsState::initFonts()
{
	if (
		!this->font.loadFromFile("Fonts/ComicNeue.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}



}
void SettingsState::initKeybinds()
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
void SettingsState::initGui()
{
	//std::string li[3] = { "1920x1080","1366x768", "800x600" };
	std::vector<std::string> modes_str;
	for (auto &i : this->modes) 
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}

	this->dropDownList["RESOLUTION"] = new gui::DrowDownList(43.f, 65.f, 100.f, 50.f, font, modes_str.data(), modes_str.size());


	this->buttons["EXIT_STATE"] = new gui::Button(
		100.f, 400.f, 100.f, 50.f,
		&this->font, "Quit", 24,
		sf::Color(223, 230, 233, 200), sf::Color(250, 250, 250, 250), sf::Color(223, 230, 233, 200),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
		);

	this->buttons["APPLY"] = new gui::Button(
		205.f, 400.f, 100.f, 50.f,
		&this->font, "Apply", 24,
		sf::Color(223, 230, 233, 200), sf::Color(250, 250, 250, 250), sf::Color(223, 230, 233, 200),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
		);
}
void SettingsState::initText()
{
	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(sf::Vector2f(40.f, 40.f));
	this->optionsText.setCharacterSize(24);
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));

	this->optionsText.setString(
		"Resolution - ScreenMode - Vsync - AA"
		);

}


//// CONSTRUCTORS / DESTRUCTORS
SettingsState::SettingsState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->initText();
}
SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	auto it2 = this->dropDownList.begin();
	for (it2 = this->dropDownList.begin(); it2 != this->dropDownList.end(); ++it2)
	{
		delete it2->second;
	}
}
//// CONSTRUCTORS / DESTRUCTORS


//// ACCESSORS

//// ACCESSORS


//// FUNCTIONS
void SettingsState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")))) {
		this->endState();
	}
}
void SettingsState::updateGui(const float& dt)
{
	/*UPDATE ALL THE GUI ELEMENTS IN THE STATE AND HANDLES THEIR FUNCTIONLAITY*/

	// BUTTONS
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	// QUIT THE SETTINGS_STATE
	//if (this->buttons["EXIT_STATE"]->isPressed())
	//{
	//	this->endState();
	//}

	// APPLY CHANGES
	if (this->buttons["APPLY"]->isPressed())
	{
		this->stateData->gfxSettings->resolution = this->modes[this->dropDownList["RESOLUTION"]->getActiveElementId()];
		this->window->create(*&this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);
	}

	// DROPDOWNLISTS
	for (auto& it : this->dropDownList)
	{
		it.second->update(this->mousePosWindow, dt);
	}
}
void SettingsState::update(const float& dt)
{
	this->updateInput(dt);
	this->updateMousePositions();

	this->updateGui(dt);
}
void SettingsState::renderGui(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

	for (auto& it : this->dropDownList)
	{
		it.second->render(target);
	}
}
void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);

	this->renderGui(*target);

	target->draw(this->optionsText);

	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y + 15);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x  << " "  << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);

}
//// FUNCTIONS