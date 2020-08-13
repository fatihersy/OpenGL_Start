#ifndef MAINMANUSTATE_H
#define MAINMANUSTATE_H

#include "GameState.h"
#include "EditorState.h"
#include "SettingsState.h"
#include "Gui.h"

class GameState;
class EditorState;
class SettingsState;
class Gui;

class MainMenuState :
	public State
{
private:
	//Variables
	//GraphicsSettings& gfxSettings;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;

	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();

public:
	MainMenuState(StateData* state_data);
	virtual ~MainMenuState();


	// FUNCTIONS
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);

};

#endif // !MAINMANUSTATE_H




