#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_h

#include "State.h"
#include "Gui.h"
#include "GraphicsSettings.h"

class State;
class Gui;
class GraphicsSettings;

class SettingsState :
	public State
{
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::DrowDownList*> dropDownList;

	sf::Text optionsText;
	std::vector<sf::VideoMode> modes;

	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initGui();
	void initText();


public:
	//// CONSTRUCTORS / DESTRUCTORS
	SettingsState(StateData* state_data);
	virtual ~SettingsState();
	//// CONSTRUCTORS / DESTRUCTORS


	//// ACCESSORS
	//// ACCESSORS


	//// FUNCTIONS
	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void update(const float& dt);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
	//// FUNCTIONS
};

#endif